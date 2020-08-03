/*
 * Copyright 2020 Denis Yaroshevskiy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';

function replaceStringValuesWithNumbers(loaded) {
  return Object.fromEntries(Object.entries(loaded).map(
    ([key, value]) => {
      if (isNaN(value)) { return [key, value] };
      if (key == 'time') { return [key, parseFloat(value)]; }
      return [key, parseInt(value)];
    }
  ));
}

function valuesByKeys(measurements) {
  let res = {};
  for (const m of measurements) {
    for (const [k, v] of Object.entries(m)) {
      if (!res[k]) res[k] = [];
      res[k].push(v);
    }
  }
  return res;
}

async function loadMeasurements() {
  if (!loadMeasurements.cache) {
    let url = "data/all.json";
    if (typeof UNSQ_EVE_COMMIT !== 'undefined') {
      url = `https://raw.githubusercontent.com/DenisYaroshevskiy/unsq_eve/${UNSQ_EVE_COMMIT}/data/all.json`
    }
    console.log(url);
    const loaded = await fetch(url).then(async (raw) => raw.json());
    loadMeasurements.cache = loaded.map(replaceStringValuesWithNumbers);
  }
  return loadMeasurements.cache;
}

async function measurementsByKeys() {
  if (!measurementsByKeys.cache) {
    measurementsByKeys.cache = valuesByKeys(await loadMeasurements());
  }
  return measurementsByKeys.cache;
}

function isSubset(small, big) {
  for (const [key, value] of Object.entries(small)) {
    if (big[key] !== value) return false;
  }
  return true;
}

function setDifference(big, small) {
  let res = {}
  for (const [key, value] of Object.entries(big)) {
    if (!small.hasOwnProperty(key)) {
      res[key] = value;
    }
  }
  return res;
}

function arraysEqual(x, y) {
  if (x.length != y.length) return false;

  for (let i = 0; i < x.length; ++i) {
    if (x[i] !== y[i]) return false;
  }

  return true;
}

function partitionByKeys(objects, keys) {
  let res = [];
  for (const o of objects) {
    let indx = res.findIndex(e => {
      for (const key of keys) if (e[0][key] !== o[key]) return false;
      return true;
    });
    if (indx === -1) {
      indx = res.length;
      res.push([]);
    }
    res[indx].push(o);
  }

  return res;
}

const REDUCE_OPERATIONS = ['min', 'max', 'minmax'];

function processVaryingKeys(varying) {
  let x = undefined;
  let y = undefined;
  let selection = [];
  let reduce = undefined;
  let reduction_keys = [];
  for (const [key, value] of Object.entries(varying)) {
    if (value == 'x') {
      if (x) throw new Error(`duplicated x: ${x}, ${key}`);
      x = key;
      continue;
    }
    if (value == 'y') {
      if (y) throw new Error(`duplicated y: ${y}, ${key}`);
      y = key;
      continue;
    }
    if (value == 'selection') {
      selection.push(key);
      continue;
    }
    if (REDUCE_OPERATIONS.indexOf(value) !== -1) {
      reduction_keys.push(key);
      reduce = value;
      continue;
    }
    throw new Error('unknown variation on ${key}: ${value}');
  }

  if (!y) throw new Error('y is not defined');
  return { x, y, selection, reduce, reduction_keys };
}

function minByKey(xs, key) {
  return xs.reduce((x1, x2) => x2[key] < x1[key] ? x2 : x1);
}

function maxByKey(xs, key) {
  return xs.reduce((x1, x2) => x2[key] >= x1[key] ? x2 : x1);
}

function reduceInGroups(objects, groupKey, reduction) {
  const sameKey = partitionByKeys(objects, [groupKey]);
  const valuesForKey = sameKey.map(reduction);
  return valuesForKey.flat();
}

function applyReduction(selections, varying) {
  if (!varying.reduce) return selections;

  const doReduction = varying.x ?
    (objects, reduction) => reduceInGroups(objects, varying.x, reduction) :
    (objects, reduction) => [reduction(objects)];

  if (varying.reduce === 'minmax') {
    varying.selection.push('variation');
  }

  let res = [];

  for (const sel of selections) {
    if (varying.reduce === 'min') {
      res.push(doReduction(sel, ms => minByKey(ms, varying.y)));
    } else if (varying.reduce === 'max') {
      res.push(doReduction(sel, ms => maxByKey(ms, varying.y)));
    } else if (varying.reduce === 'minmax') {
      let min = doReduction(sel, ms => minByKey(ms, varying.y));
      let max = doReduction(sel, ms => maxByKey(ms, varying.y));
      min = JSON.parse(JSON.stringify(min));
      max = JSON.parse(JSON.stringify(max));
      min.variation = 'min';
      max.variation = 'max';
      res.push(min);
      res.push(max);
    }
  }

  return res;
}

function makeLinesSelectionObject(ms, varying) {
  const name = varying.selection.map(key => ms[0][key]).join('/');
  const x = ms.map(m => m[varying.x]);
  const y = ms.map(m => m[varying.y]);
  return { name, x, y };
}

function makeTitle(varying, fixed) {
  let title_elements = Object.entries(fixed).map(key_value => `${key_value[0]} : ${key_value[1]}`);
  if (varying.reduce) {
    let reduction_key = varying.reduction_keys.join(',');
    title_elements.push(`${reduction_key} : ${varying.reduce}`);
  }
  return title_elements.join(' | ');
}

function makeBarsTrace(ms, traceSelections, varying) {
  const name = varying.selection.map(key => ms[0][0][key]).join('/');
  const x = ms.map(m => {
    return varying.selection.map(key => m[0][key]).join('/')
  });
  const y = ms.map(m => m[0][varying.y]);
  return { name, x, y };
}

function makeBarsTraces(selections, varying) {
  let traceGroups = selections.map(s => [s]);
  let traceSelections = [];

  /*if (varying.selection.length > 1) {
    traceSelections = [varying.selection]
    traceGroups = partitionByKeys(selections.flat(), traceSelections);
  }*/
  console.log('traceGroups: ', traceGroups);

  return traceGroups.map(ms => makeBarsTrace(ms, traceSelections, varying));
}

function visualizationDataFromMeasurements(varying, fixed, measurements) {
  measurements = measurements.filter(e => isSubset(fixed, e));
  measurements = measurements.map(e => setDifference(e, fixed));
  varying = processVaryingKeys(varying);
  let selections = partitionByKeys(measurements, varying.selection);
  selections = applyReduction(selections, varying);
  const title = makeTitle(varying, fixed);

  if (varying.x) {
    // Lines
    return {
      title,
      x_title: varying.x,
      y_title: varying.y,
      lines: selections.map(ms => makeLinesSelectionObject(ms, varying))
    };
  }

  // Bars
  return {
    title,
    y_title: varying.y,
    traces: makeBarsTraces(selections, varying)
  }
}

function drawLinesBenchmark(element, width, data, traceFilter) {
  const traces = data.lines.map(line => {
    return {
      name: line.name,
      x: line.x,
      y: line.y,
      marker: { size: 8 },
      line: { size: 3 },
      type: 'scatter'
    };
  }).filter(traceFilter);

  const layout = {
    title: data.title,
    xaxis: {
      type: 'category',
      title: {
        text: data.x_title,
      }
    },
    yaxis: {
      title: {
        text: data.y_title,
      },
      rangemode: 'tozero',
      autorange: true
    },
    width: width,
    height: 600,
  };

  Plotly.newPlot(element, traces, layout);
}

function drawBarsBenchmars(element, width, data, traceFilter) {
  const traces = data.traces.map((trace) => {
    return {
      name: trace.name,
      x: trace.x,
      y: trace.y,
      type: 'bar'
    }
  }).filter(traceFilter);

  const layout = {
    title: data.title,
    barmode: 'group',
    width: width,
    height: 600,
    yaxis: {
      title: {
        text: data.y_title,
      }
    }
  };
  Plotly.newPlot(element, traces, layout);
}

function drawBenchmark(element, width, data, traceFilter) {
  if (data.x_title) {
    drawLinesBenchmark(element, width, data, traceFilter);
  } else {
    drawBarsBenchmars(element, width, data, traceFilter);
  }
}

function addTextInput(parent, width, defaultInput, onChanged) {
  let input = document.createElement("INPUT");

  let errorMessage = document.createElement('div');
  const NO_ERROR = '<br>Parsed succesfully<br/>'
  errorMessage.innerHTML = NO_ERROR;

  input.setAttribute('type', 'text');
  input.style.width = width;
  input.setAttribute('value', defaultInput);

  input.addEventListener('input', () => {
    try {
      onChanged(input.value);
      errorMessage.innerHTML = NO_ERROR;
    } catch (er) {
      console.log(er);
      errorMessage.innerHTML = `<br/>${er.message}<br/>`;
    }
  });
  parent.appendChild(input);
  parent.appendChild(errorMessage);

  return input;
}

const CONTROL_VALUES = ['x', 'y', 'min', 'max', 'minmax', 'selection'];

function inputParseValueCheck(input, keys2values) {
  for (const [k, v] of Object.entries(input)) {
    if (CONTROL_VALUES.includes(v)) continue;
    if (!keys2values[k].includes(v)) {
      throw Error(`No matches for ${k} : ${v}`);
    }
  }
}

function inputParse(text, byKeys) {
  const input = JSON.parse(text);

  const inputKeys = Object.keys(input);
  const benchKeys = Object.keys(byKeys);

  for (const key of inputKeys) {
    if (!benchKeys.includes(key)) {
      throw new Error(`unknown key:${key}`);
    }
  }
  inputParseValueCheck(input, byKeys);
  const varying =
    Object.fromEntries(Object.entries(input).filter((kv) => CONTROL_VALUES.includes(kv[1])));
  const fixed =
    Object.fromEntries(Object.entries(input).filter((kv) => !CONTROL_VALUES.includes(kv[1])));
  return [varying, fixed];
}

function filterParse(filter) {
  const input = JSON.parse(filter);
  if (input.length === 0) return (trace) => true;

  return (trace) => {
    for (let ok of input) {
      if (trace.name.includes(ok)) return true;
    }
    return false;
  }
}

async function dynamicEntryPoint(elementID, defaultSelection, defaultFilter = []) {
  const element = document.getElementById(elementID);
  const measurements = await loadMeasurements();
  const byKeys = await measurementsByKeys();

  let drawHere = undefined;
  let selection = JSON.stringify(defaultSelection, undefined, 2);
  let filter = JSON.stringify(defaultFilter, undefined, 2);

  const redrawCallback = () => {
    const [varying, fixed] = inputParse(selection, byKeys);
    const traceFilter = filterParse(filter);
    const asVisualized = visualizationDataFromMeasurements(varying, fixed, measurements);
    drawBenchmark(drawHere, 1200, asVisualized, traceFilter);
  };

  addTextInput(element, '1200px', selection, (value) => {
    selection = value;
    redrawCallback();
  });
  addTextInput(element, '1200px', filter, (value) => {
    filter = value;
    redrawCallback();
  });

  drawHere = element.appendChild(document.createElement('div'));
  redrawCallback();
}

async function presentationEntryPoint(elementID, selection_, filter_ = []) {
  const element = document.getElementById(elementID);
  const measurements = await loadMeasurements();
  const byKeys = await measurementsByKeys();

  let selection = JSON.stringify(selection_, undefined, 2);
  let filter = JSON.stringify(filter_, undefined, 2);
  const [varying, fixed] = inputParse(selection, byKeys);
  const traceFilter = filterParse(filter);
  const asVisualized = visualizationDataFromMeasurements(varying, fixed, measurements);

  drawBenchmark(element, 1000, asVisualized, traceFilter);
}

function miniumTimesBySizeTemplate(elementID) {
  dynamicEntryPoint(elementID, {
    name: 'find 0',
    algorithm: 'selection',
    type: 'char',
    size: 'x',
    time: 'y',
    padding: 'min',
    percentage: 100,
    group: "intel_9700K"
  });
}

function codeAlignmentTemplate(elementID) {
  dynamicEntryPoint(elementID, {
    name: 'find 0',
    size: 1000,
    type: 'char',
    algorithm: 'selection',
    padding: 'minmax',
    time: 'y',
    percentage: 100,
    group: "intel_9700K"
  });
}

/// tests ---------------------------------

function exceptTrue(test, msg) {
  if (test) return;
  throw new Error(`Expectation failed: ${msg}`);
}

function expectEqual(expected, actual, msg = '') {
  const expectedStr = JSON.stringify(expected);
  const actualStr = JSON.stringify(actual);

  if (expectedStr !== actualStr) {
    throw new Error(`Expectation failed: expected=${expectedStr},  actual=${actualStr}\n${msg}`);
  }
}

function expectThrows(callback, msg_part) {
  try {
    callback();
    throw new Error(`expected to throw: ${msg_part}`);
  } catch (ex) {
    if (ex.message.includes(msg_part)) return;
    throw new Error(`unexpected error: ${ex.message} instead of ${msg_part}`);
  }
}

function isSubsetTests() {
  const obj1 = { a: 'a', b: 3 };
  const obj2 = { a: 'a', b: 3, c: 'c' };
  exceptTrue(isSubset(obj1, obj2), "subset obj1, obj2");
  exceptTrue(!isSubset(obj2, obj1), "!subset obj2, obj1");

  const obj3 = { a: 'a', b: 3, d: 'd' };
  exceptTrue(!isSubset(obj3, obj2), "!subset obj2, obj1");
}

function setDifferenceTests() {
  const obj1 = { a: 'a', b: 3 };
  const obj2 = { a: 'a', b: 3, c: 'c' };
  const obj3 = setDifference(obj2, obj1);
  expectEqual({ c: 'c' }, obj3);
}

function arraysEqualTests() {
  const arr1 = [1, "123", 4];
  const arr2 = [1, "123", 5];

  exceptTrue(arraysEqual(arr1, arr1), "arr1 == arr1");
  exceptTrue(!arraysEqual(arr1, arr2), "arr1 != arr2");
}

function partitionByKeysTests() {
  const data = [
    {
      a: 1,
      b: 2,
      c: 3
    },
    {
      a: 1,
      b: 2,
      c: 4
    },
    {
      a: 2,
      b: 2,
      c: 4
    }
  ];

  {
    const keys = ['a', 'b'];
    expectEqual([[data[0], data[1]], [data[2]]], partitionByKeys(data, keys));
  }

  {
    const keys = ['b'];
    expectEqual([data], partitionByKeys(data, keys));
  }
}

function reductionsTests() {
  const data = [
    { a: 1 },
    { a: 0 }
  ];
  expectEqual(data[1], minByKey(data, 'a'));
  expectEqual(data[0], maxByKey(data, 'a'));
}

function visualizationDataFromMeasurementsTests() {
  const data = [
    {
      name: 'bench1',
      size: 1000,
      padding: 0,
      alg: 'alg1',
      variation: 0,
      percentage: 5,
      time: 0.1
    },
    {
      name: 'bench1',
      size: 1000,
      padding: 1,
      alg: 'alg1',
      variation: 0,
      percentage: 5,
      time: 0.25
    },
    {
      name: 'bench2',
      size: 1000,
      padding: 0,
      alg: 'alg1',
      variation: 0,
      percentage: 5,
      time: 0.25
    },
    {
      name: 'bench2',
      size: 1000,
      padding: 1,
      alg: 'alg1',
      variation: 0,
      percentage: 5,
      time: 0.25
    },
    {
      name: 'bench1',
      size: 1000,
      padding: 0,
      alg: 'alg2',
      variation: 1,
      percentage: 5,
      time: 0.4
    },
    {
      name: 'bench1',
      size: 1000,
      padding: 1,
      alg: 'alg2',
      variation: 1,
      percentage: 5,
      time: 0.3
    },
  ];

  const varying = {
    percentage: 'x',
    time: 'y',
    alg: 'selection',
    variation: 'selection',
    padding: 'min'
  };
  const fixed = {
    name: 'bench1',
    size: 1000
  };

  const expected = {
    title: "name : bench1 | size : 1000 | padding : min",
    x_title: "percentage",
    y_title: "time",
    lines: [{
      name: 'alg1/0',
      x: [5],
      y: [0.1]
    },
    {
      name: 'alg2/1',
      x: [5],
      y: [0.3]
    }]
  };

  expectEqual(expected, visualizationDataFromMeasurements(varying, fixed, data));
}

function inputParseTests() {
  const keys2values = {
    group: ['intel_9700K'],
    algorithm: ['std::find', 'unsq::find_unguarded'],
    percentage: [10],
    time: []
  };

  expectThrows(() => {
    inputParse('{"some_key": "value"}', keys2values);
  }, 'unknown key');

  expectThrows(() => {
    inputParse('{"group": "blabla"}', keys2values);
  }, 'No matches');

  const [varying, fixed] =
    inputParse('{"group": "intel_9700K", "algorithm": "selection", "percentage": "x", "time": "y"}', keys2values);
  expectEqual(varying, {
    algorithm: 'selection',
    percentage: 'x',
    time: 'y'
  });
  expectEqual(fixed, {
    group: 'intel_9700K'
  });
}

function valuesByKeysTests() {
  const measurements = [
    { a: 3, b: 5 },
    { a: 4, c: 6 }
  ];
  const expected = {
    a: [3, 4],
    b: [5],
    c: [6]
  };
  expectEqual(expected, valuesByKeys(measurements));
}

async function listOfTests() {
  isSubsetTests();
  setDifferenceTests();
  arraysEqualTests();
  partitionByKeysTests();
  reductionsTests();
  visualizationDataFromMeasurementsTests();
  inputParseTests();
  valuesByKeysTests();
}

async function runTests(elementID) {
  let element = document.getElementById(elementID);

  try {
    listOfTests();
  } catch (er) {
    element.innerHTML = `Tests failed. error=${er.message}<br/><br/>`
  }
}
