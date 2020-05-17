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
    const loaded = await fetch("data/all.json").then(async (raw) => raw.json());
    loadMeasurements.cache = loaded.map(replaceStringValuesWithNumbers);
  }
  return loadMeasurements.cache;
}

async function measurementsByKeys() {
  if (!measurementsByKeys.cache){
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

  if (!x) throw new Error('x is not defined');
  if (!y) throw new Error('y is not defined');
  if (selection.length == 0) throw new Error('selection options are not specified');
  return { x, y, selection, reduce, reduction_keys };
}

function minByKey(xs, key) {
  return xs.reduce((x1, x2) => x2[key] < x1[key] ? x2 : x1);
}

function maxByKey(xs, key) {
  return xs.reduce((x1, x2) => x2[key] >= x1[key] ? x2 : x1);
}

function reduceInGroups(objects, groupKey, redaction) {
  const sameKey = partitionByKeys(objects, [groupKey]);
  const valuesForKey = sameKey.map(redaction);
  return valuesForKey.flat();
}

function applyReduction(selections, varying) {
  if (!varying.reduce) return selections;

  if (varying.reduce === 'minmax') {
    varying.selection.push('variation');
  }

  let res = [];

  for (const sel of selections) {
    if (varying.reduce === 'min') {
      res.push(reduceInGroups(sel, varying.x, ms => minByKey(ms, varying.y)));
    } else if (varying.reduce === 'max') {
      res.push(reduceInGroups(sel, varying.x, ms => maxByKey(ms, varying.y)));
    } else if (varying.reduce === 'minmax') {
      let min = reduceInGroups(sel, varying.x, ms => minByKey(ms, varying.y));
      let max = reduceInGroups(sel, varying.x, ms => maxByKey(ms, varying.y));
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

function makeSelectionObject(ms, varying) {
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

function visualizationDataFromMeasurements(varying, fixed, measurements) {
  measurements = measurements.filter(e => isSubset(fixed, e));
  measurements = measurements.map(e => setDifference(e, fixed));
  varying = processVaryingKeys(varying);
  let selections = partitionByKeys(measurements, varying.selection);
  selections = applyReduction(selections, varying);
  return {
    title: makeTitle(varying, fixed),
    x_title: varying.x,
    y_title: varying.y,
    lines: selections.map(ms => makeSelectionObject(ms, varying))
  };
}

function drawBenchmark(element, data) {
  const traces = data.lines.map(line => {
    return {
      name: line.name,
      x: line.x,
      y: line.y,
      marker: { size: 8 },
      line: { size: 3 },
      type: 'scatter'
    };
  });

  console.log(data);

  const layout = {
    title: data.title,
    xaxis: {
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
    width: 800,
    height: 600,
  };

  Plotly.newPlot(element, traces, layout);
}

function addTextInput(parent, defaultInput, onChanged) {
  let input = document.createElement("INPUT");
  input.setAttribute('type', 'text');
  input.style.width = '400px'
  input.setAttribute('value', defaultInput);

  input.addEventListener('input', () => {
    console.log(input.value);
    onChanged(input.value);
  });
  parent.appendChild(input);
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

async function dynamicEntryPoint(elementID) {
  const element = document.getElementById(elementID);
  const measurements = await loadMeasurements();
  const byKeys = await measurementsByKeys();

  const defaultInput = {
    size: 'x',
    time: 'y',
    padding: 'min',
    algorithm: 'selection',
    type: 'selection',
    name: 'find 0',
    percentage : 100
  };

  let drawHere = undefined;

  const redrawCallback = (text) => {
    try {
      const [varying, fixed] = inputParse(text, byKeys);
      const asVisualized = visualizationDataFromMeasurements(varying, fixed, measurements);
      drawBenchmark(drawHere, asVisualized);
    } catch (er) {
      console.log(er);
    }
  };

  let input = addTextInput(element, JSON.stringify(defaultInput, undefined, 2), redrawCallback);
  drawHere = element.appendChild(document.createElement('div'));
  redrawCallback(input.value);
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
    percentage: [ 10 ],
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
    algorithm : 'selection',
    percentage : 'x',
    time : 'y'
  });
  expectEqual(fixed, {
    group: 'intel_9700K'
  });
}

function valuesByKeysTests() {
  const measurements = [
    { a : 3, b : 5},
    { a : 4, c : 6}
  ];
  const expected = {
    a : [3, 4],
    b : [5],
    c : [6]
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
    element.innerHTML = `Tests passed<br/><br/>`
  } catch (er) {
    element.innerHTML = `Tests failed. error=${er.message}<br/><br/>`
  }
}
