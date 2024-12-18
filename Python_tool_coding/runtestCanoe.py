# -----------------------------------------------------------------------------
# Example: Test Feature Set via Python
# 
# This sample demonstrates how to start the test modules and test 
# configurations via COM API using a Python script.
# The script uses the included PythonBasicEmpty.cfg configuration but is  
# working also with any other CANoe configuration containing test modules  
# and test configurations. 
# 
# Limitations:
#  - only the first test environment is supported. If the configuration 
#    contains more than one test environment, the other test environments 
#    are ignored
#  - the script does not wait for test reports to be finished. If the test
#    reports are enabled, they may run in the background after the test is 
#    finished
# -----------------------------------------------------------------------------
# Copyright (c) 2017 by Vector Informatik GmbH.  All rights reserved.
# -----------------------------------------------------------------------------

import time, os, msvcrt
from win32com.client import *
from win32com.client.connect import *
import subprocess

# -----------------------------------------------------------------------------
# 线程等待处理
# 如果条件为假（con = False），则程序一直等待挂起；
# 如果条件为真（con = True），则程序跳出；
# -----------------------------------------------------------------------------
def DoEvents():
    # 在当前线程下弹出所有等待消息
    pythoncom.PumpWaitingMessages()
    # 延时0.1秒，线程挂起
    time.sleep(.1)


def DoEventsUntil(cond):
    while not cond():
        DoEvents()

# -----------------------------------------------------------------------------
# 定义CANoe应用
# -----------------------------------------------------------------------------
class CanoeSync(object):
    """Wrapper class for CANoe Application object"""
    #定义类变量
    Started = False
    Stopped = False
    ConfigPath = ""
    # -------------------------------------------------------------------------
    # 构造方法，Self代表类的示例
    # -------------------------------------------------------------------------
    def __init__(self):
        # 创造CANoe应用对象实例
        app = DispatchEx('CANoe.Application')
        # CANoe工程加载或新建时不能被修改
        app.Configuration.Modified = False
        # CANoe版本
        ver = app.Version
        print('Loaded CANoe version ',
              ver.major, '.',
              ver.minor, '.',
              ver.Build, '...', sep='')
        self.App = app
        # 获取CANoe测量配置
        self.Measurement = app.Measurement
        # 匿名函数，获取CANoe的运行状态
        self.Running = lambda: self.Measurement.Running
        # 匿名函数，等待CANoe启动
        self.WaitForStart = lambda: DoEventsUntil(lambda: CanoeSync.Started)
        # 匿名函数，等待CANoe停止
        self.WaitForStop = lambda: DoEventsUntil(lambda: CanoeSync.Stopped)
        # 定义Measurement时间
        WithEvents(self.App.Measurement, CanoeMeasurementEvents)
        # 获取CANoe环境变量
        self.Environment = app.Environment

    # -------------------------------------------------------------------------
    # 加载CANoe工程，cfgPath - 相对路径
    # -------------------------------------------------------------------------
    def Load(self, cfgPath):
        # current dir must point to the script file
        # 把当前工程根目录和给定子目录结合起来
        cfg = os.path.join(os.curdir, cfgPath)
        # 找到CANoe的绝对路径
        cfg = os.path.abspath(cfg)
        print('Opening: ', cfg)
        # 返回CANoe工程的路径名称
        self.ConfigPath = os.path.dirname(cfg)
        # 定义CANoe仿真配置
        self.Configuration = self.App.Configuration
        # 打开CANoe工程
        self.App.Open(cfg)

    # -------------------------------------------------------------------------
    # 加载TestModules测试配置
    # -------------------------------------------------------------------------
    def LoadTestSetup(self, testsetup):
        # 返回测试配置
        self.TestSetup = self.App.Configuration.TestSetup
        # 把当前工程根目录和给定子目录结合起来
        path = os.path.join(self.ConfigPath, testsetup)
        # 把.tes测试环境TestEnvironments加入TestSetup
        testenv = self.TestSetup.TestEnvironments.Add(path)
        # ITestEnvironment2属于Vector自定义强制类型
        testenv = CastTo(testenv, "ITestEnvironment2")
        # TestModules property to access the test modules
        # 创建TestModules列表
        self.TestModules = []
        # Test Module添加到.tes中，List末尾添加新对象
        self.TraverseTestItem(testenv, lambda tm: self.TestModules.append(CanoeTestModule(tm)))

    # -------------------------------------------------------------------------
    # 加载vTEST测试配置
    # -------------------------------------------------------------------------
    def LoadTestConfiguration(self, testcfgname, testunits):
        """ Adds a test configuration and initialize it with a list of existing test units """
        # 添加Test Configurations到CANoe工程
        tc = self.App.Configuration.TestConfigurations.Add()
        # Test Configurations名称
        tc.Name = testcfgname
        # ITestUnits2属于Vector自定义强制类型
        tus = CastTo(tc.TestUnits, "ITestUnits2")
        # 遍历所有Test Unit，加入Test Configurations
        for tu in testunits:
            tus.Add(tu)
        # TestConfigs property to access the test configuration
        self.TestConfigs = [CanoeTestConfiguration(tc)]

    def Start(self):
        if not self.Running():
            # 如果CANoe未启动，则启动CANoe
            self.Measurement.Start()
            # 等待CANoe启动
            self.WaitForStart()

    def Stop(self):
        if self.Running():
            # 如果CANoe已运行，则停止运行CANoe
            self.Measurement.Stop()
            # 等待停止运行CANoe
            self.WaitForStop()

    def RunTestModules(self):
        """ starts all test modules and waits for all of them to finish"""
        # start all test modules
        for tm in self.TestModules:
            tm.Start()

        # wait for test modules to stop
        # 如果当前CANoe工程中所有test modules在运行中或未激活，则程序等待
        while not all([not tm.Enabled or tm.IsDone() for tm in app.TestModules]):
            DoEvents()

    def RunTestConfigs(self):
        """ starts all test configurations and waits for all of them to finish"""
        # start all test configurations
        for tc in self.TestConfigs:
            tc.Start()

        # wait for test modules to stop
        # 如果当前CANoe工程中所有test configurations在运行中或未激活，则程序等待
        while not all([not tc.Enabled or tc.IsDone() for tc in app.TestConfigs]):
            DoEvents()

    # -------------------------------------------------------------------------
    # 循环遍历.tse里Test Modules和子文件
    # -------------------------------------------------------------------------
    def TraverseTestItem(self, parent, testf):
        # 遍历.tse中所有Test Modules
        for test in parent.TestModules:
            # 添加到Test Modules集合中
            testf(test)
        # 在.tse文件夹中遍历子文件
        for folder in parent.Folders:
            # 添加到Test Modules集合中
            found = self.TraverseTestItem(folder, testf)
 

class CanoeMeasurementEvents(object):
    """Handler for CANoe measurement events"""

    def OnStart(self):
        CanoeSync.Started = True
        CanoeSync.Stopped = False
        print("< measurement started >")

    def OnStop(self):
        CanoeSync.Started = False
        CanoeSync.Stopped = True
        print("< measurement stopped >")


class CanoeTestModule:
    """Wrapper class for CANoe TestModule object"""

    def __init__(self, tm):
        self.tm = tm
        self.Events = DispatchWithEvents(tm, CanoeTestEvents)
        self.Name = tm.Name
        self.IsDone = lambda: self.Events.stopped
        self.Enabled = tm.Enabled

    def Start(self):
        if self.tm.Enabled:
            self.tm.Start()
            self.Events.WaitForStart()


class CanoeTestConfiguration:
    """Wrapper class for a CANoe Test Configuration object"""

    def __init__(self, tc):
        self.tc = tc
        self.Name = tc.Name
        self.Events = DispatchWithEvents(tc, CanoeTestEvents)
        self.IsDone = lambda: self.Events.stopped
        self.Enabled = tc.Enabled

    def Start(self):
        if self.tc.Enabled:
            self.tc.Start()
            self.Events.WaitForStart()


class CanoeTestEvents:
    """Utility class to handle the test events"""

    def __init__(self):
        self.started = False
        self.stopped = False
        self.WaitForStart = lambda: DoEventsUntil(lambda: self.started)
        self.WaitForStop = lambda: DoEventsUntil(lambda: self.stopped)

    def OnStart(self):
        self.started = True
        self.stopped = False
        print("<", self.Name, " started >")

    def OnStop(self, reason):
        self.started = False
        self.stopped = True
        print("<", self.Name, " stopped >")


# -----------------------------------------------------------------------------
# main
# -----------------------------------------------------------------------------
app = CanoeSync()

# loads the sample configuration
app.Load('CANoePro\CANoePro_autotest.cfg')

# add test modules to the configuration
# app.LoadTestSetup('TestEnvironments\Test Environment.tse')

# add a test configuration and a list of test units
# app.LoadTestConfiguration('TestConfiguration', ['TestConfiguration\EasyTest\EasyTest.vtuexe'])

# start the measurement
app.Start()

# runs the test script
# 使用subprocess方法，执行adb命令
subprocess.run("adb shell am start -n com.zinthewind.air-consetting/.MainActivity",
               shell=True,
               stdout=subprocess.PIPE,
               stderr=subprocess.PIPE,
               universal_newlines=True)
# 延时1秒
time.sleep(1)
subprocess.run("adb shell input tap 778 438",
               shell=True,
               stdout=subprocess.PIPE,
               stderr=subprocess.PIPE,
               universal_newlines=True)
time.sleep(1)
# 获取CANoe工程中Environment的值
ACFunctionReqState = app.Environment.GetVariable("Env_ACFunctionReq")
print("Env_ACFunctionReq = ",ACFunctionReqState.Value)
time.sleep(1)
NM_BUS_State = app.Environment.GetVariable("Env_NM_BUS_State")
print("Env_NM_BUS_State = ", NM_BUS_State)
# bus sleep = 1
# 设置CANoe工程中Environment的值
NM_BUS_State.Value = 1
time.sleep(1)

# runs the test modules
# app.RunTestModules()

# runs the test configurations
# app.RunTestConfigs()

# wait for a keypress to end the program
print("Press any key to exit ...")
while not msvcrt.kbhit():
    DoEvents()

# stops the measurement
app.Stop()