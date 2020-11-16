# CliTestClient_readline #

一个在linux上，类似shell(使用bash的readline库)的交互式操作，常用于自定义工具，比如CLI测试工具，或网络socket CLI。

### 需要支持的特性 ###

* 类似bash,支持命令补全功能
* 类似bash,支持history输入记录功能
* 支持因异步输出屏幕，导致终端显示输入命令错误恢复
* 支持选择多种方式输入(仅直接执行一条命令，交互文件，或读取命令文件执行)




### 依赖的库 ###

* **readline**:GUN Bash使用命令行库，**相关功能直接依赖**
* **[Catch2](https://github.com/catchorg/Catch2)**:C ++的单元测试框架,主要是多使用些框架，学习学习。
* **[spdlog](https://github.com/gabime/spdlog)**:C ++的日志库,主要是多使用些框架，学习学习。
* **[gflags](https://github.com/gflags/gflags)**:可以方便的调整一些逻辑分支的走向。也可以通过flag来配置一些参数，无需每次新增配置文件和增加配置解析的逻辑.