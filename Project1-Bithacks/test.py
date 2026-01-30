#!/usr/bin/env python3

"""Test runner for 6.172, fall 2010.

TODO(rnk): Fill out the docstring comment with usage.
"""

__author__ = 'Reid Kleckner <rnk@mit.edu>'

import difflib
import os
import re
import subprocess
import sys
import time

# 终端颜色控制常量
GREEN = '\033[92;1m'
RED = '\033[91;1m'
END = '\033[0m'

QUIET = False

def print_result(result):
    """If result is True, print a green PASSED or red FAILED line otherwise."""
    if result:
        print(GREEN + 'PASSED' + END)
    else:
        print(RED + 'FAILED' + END)

def wait_for_test_process(proc, timeout):
    """Waits for a test process with a timeout, and reads stderr.

    Reading stderr while polling is important, or a deadlock can occur if the
    pipe's internal buffer fills up.
    """
    endtime = time.time() + timeout
    err_chunks = []
    while proc.returncode is None and time.time() < endtime:
        time.sleep(0.1)
        # Python 3: os.read返回bytes，需暂存后统一解码为str
        chunk = os.read(proc.stderr.fileno(), 4096)
        err_chunks.append(chunk)
        proc.poll()

    # Kill the child if it hasn't stopped yet, and wait for it.
    timed_out = False
    if proc.returncode is None:
        proc.kill()
        proc.wait()
        timed_out = True
        print('Test process timed out after 30s...')

    # Read the rest of stderr.
    chunk = b''  # Python 3: 明确为bytes类型
    while chunk:
        chunk = os.read(proc.stderr.fileno(), 4096)
        err_chunks.append(chunk)
    
    # Python 3: 合并bytes数组并解码为UTF-8字符串（处理终端输出的中文/特殊字符）
    stderr_content = b''.join(err_chunks).decode('utf-8', errors='ignore')
    lines = stderr_content.split('\n')
    return (timed_out, lines)

def test_project1(binary):
    """Test runner for project1 problems.

    Apologies for the complicatedness of the testing protocol, and also of how
    hard it is to properly run a process with a timeout.
    """
    testdir = os.path.join(os.path.dirname(binary), 'tests')
    # 处理目录不存在的异常（Python 3 更严谨的容错）
    if not os.path.exists(testdir):
        print(f"Error: Test directory '{testdir}' does not exist.")
        return (0, 0, 1)
    
    test_files = [os.path.join(testdir, fname) for fname in os.listdir(testdir)]

    num_passed = 0
    num_failed = 0
    test_index_total = 0
    for filename in test_files:
        # Python 3: 简化文件名判断（修复原代码index计算的潜在bug）
        fname = os.path.basename(filename)
        if fname.startswith('.'):
            print("Skipping file beginning with '.':", fname)
            continue
        
        done_testing = False
        test_index = 0
        while not done_testing:
            with open(os.devnull, 'w') as null:  # Python 3: 打开文件需指定模式（默认r，这里需要w）
                proc = subprocess.Popen([binary, '-t', filename],
                                        stdout=null, 
                                        stderr=subprocess.PIPE)
                (timed_out, lines) = wait_for_test_process(proc, 30.0)

            # Interpret each line.
            line_index = 0  # Python 3: 变量名规范（小写+下划线，避免关键字冲突）
            while line_index < len(lines):
                line = lines[line_index]
                line_index += 1
                
                match = re.match('Running test #(\d+)\.\.\.', line)
                if match:
                    test_index = int(match.group(1))
                
                match = re.match(' --> (.*): (PASS|FAIL)', line)
                if match:
                    passed = match.group(2) == 'PASS'
                    if passed:
                        num_passed += 1
                    else:
                        num_failed += 1
                    
                    # NOTE(TFK): Added 'or' to print failed tests.
                    if not QUIET or (QUIET and not passed):
                        testname = os.path.basename(binary) + ' ' + match.group(1)
                        print(testname.ljust(64), end=' ')  # Python 3: end='' 不换行
                        print_result(passed)
                    
                    if not passed:
                        # 防止索引越界（Python 3 容错优化）
                        for i in range(4):
                            if line_index + i < len(lines):
                                print(lines[line_index + i])
                        line_index += 4  # 跳过已打印的错误信息行
                
                if line.startswith('Done testing'):
                    test_index_total += (test_index + 1)
                    done_testing = True

            # If there was a timeout, skip the last test.
            if timed_out:
                test_index += 1
                num_failed += 1
            elif proc.returncode != 0:
                print('Nonzero return code.')
                done_testing = True
                test_index += 1
                num_failed += 1

    return (test_index_total, num_passed, num_failed)

def main(argv):
    if len(argv) < 2:
        print('Usage: test.py [--quiet] <binary> ...')
        sys.exit(1)
    
    args = argv[1:]
    if '--quiet' in args:
        global QUIET
        args.remove('--quiet')
        QUIET = True
    
    binaries = [os.path.join(os.getcwd(), arg) for arg in args]
    total_tests = 0
    total_passes = 0
    total_failed = 0
    
    for binary in binaries:
        # 检查二进制文件是否存在（Python 3 容错优化）
        if not os.path.exists(binary):
            print(f"Error: Binary file '{binary}' does not exist.")
            total_failed += 1
            continue
        (num_tests, num_passes, num_failed) = test_project1(binary)
        total_tests += num_tests
        total_passes += num_passes
        total_failed += num_failed
    
    # Python 3: f-string 格式化（更简洁易读）
    print(f'Ran {total_tests-1} test functions, {total_passes} individual tests passed, {total_failed} individual tests failed.')
    print_result(total_failed == 0)

if __name__ == '__main__':
    main(sys.argv)