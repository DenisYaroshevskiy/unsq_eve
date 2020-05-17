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

import argparse
import glob
import ntpath
import subprocess
import os

ROOT = os.path.dirname(os.path.abspath(__file__)) + '/..'
OUPUT_ROOT = f'{ROOT}/data/'
BENCHMARK_FOLDER = f'{ROOT}/build/src/bench'

assert os.path.isdir(BENCHMARK_FOLDER)


def parseOptions():
    parser = argparse.ArgumentParser(
        description="Runs bench2 benchmarks. Outputs the updated jsons")
    parser.add_argument('--filter', metavar='filter', default=None,
                        help='comma separated starts of benchmarks to run')
    parser.add_argument('processor', metavar='processor')
    options = parser.parse_args()

    return options


def findProcessorFolder(processor):
    expectedPath = f'{OUPUT_ROOT}/{processor}'
    print(expectedPath)
    assert os.path.isdir(expectedPath)
    return expectedPath


def getAllBenchmars():
    return [x for x in os.listdir(BENCHMARK_FOLDER)
            if not x.startswith('CMake') and not x.startswith('cmake')]


def filterBecnhmarks(benchmarks, filter_):
    if not filter_:
        return benchmarks
    allowed = filter_.split(',')

    def isSelected(x):
        return len([pref for pref in allowed if x.startswith(pref)]) > 0

    return [x for x in benchmarks if isSelected(x)]


def runBenchmark(bench, out):
    args = [bench, '--benchmark_out_format=json', '--benchmark_out=' + out]
    subprocess.call(args)


def runBenchmarks(toRun, outputFolder):
    for x in toRun:
        output = outputFolder + '/' + x + '.json'
        binary = BENCHMARK_FOLDER + '/' + x
        runBenchmark(binary, output)


def main():
    options = parseOptions()
    outputFolder = findProcessorFolder(options.processor)
    allBenchmars = getAllBenchmars()
    toRun = filterBecnhmarks(allBenchmars, options.filter)
    runBenchmarks(toRun, outputFolder)


if __name__ == '__main__':
    main()
