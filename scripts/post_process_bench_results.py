"""
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
 *
"""

import itertools
import json
import os

ROOT = os.path.dirname(os.path.abspath(__file__)) + '/..'
BENCH_RESULTS = f'{ROOT}/data/'
OUPUT = f'{BENCH_RESULTS}/all.json'

assert os.path.isdir(BENCH_RESULTS)


def pathForGroup(group):
    return f"{BENCH_RESULTS}/{group}"


def allGroups():
    return [x for x in os.listdir(BENCH_RESULTS) if os.path.isdir(pathForGroup(x))]


def flatten(arr):
    return list(itertools.chain(*arr))


def loadGoogleBenchmarkOutput(file):
    with open(file) as json_file:
        data = json.load(json_file)
        return data['benchmarks']


def parseParameter(parameter):
    split = parameter.split(':')
    key = split[0]
    value = ':'.join(split[1:])
    return [key, value]


def parseMeasurement(measurement):
    parsedParameters = [parseParameter(x)
                        for x in measurement['name'].split('/')[1:]]
    asDict = dict(parsedParameters)
    asDict['time'] = measurement['real_time']
    return asDict


def postProcessGoogleBenchmarOutput(output):
    return [parseMeasurement(x) for x in output]


def allJsonsInAGroup(group):
    groupPath = pathForGroup(group)
    paths = [f'{groupPath}/{x}' for x in os.listdir(groupPath)]
    paths = [x for x in paths if os.path.isfile(x) and x.endswith('.json')]
    return paths


def transformGroupResults(group, jsons):

    def processOne(group, path):
        raw = loadGoogleBenchmarkOutput(path)
        transformed = postProcessGoogleBenchmarOutput(raw)
        for x in transformed:
            x['group'] = group
        return transformed

    return flatten([processOne(group, x) for x in jsons])


def dumpOutput(prepared):
    with open(OUPUT, 'w') as outfile:
        json.dump(prepared, outfile)


def compileResultingFile():
    groups = allGroups()
    groups2jsons = [(x, allJsonsInAGroup(x)) for x in groups]
    prepared = flatten([transformGroupResults(group, jsons)
                        for group, jsons in groups2jsons])
    dumpOutput(prepared)
    print(f'Result was written to : {OUPUT}')


def main():
    compileResultingFile()


if __name__ == "__main__":
    main()
