# 发布

公开源码仓库：[HelloClyde/BBK9588-sango](https://github.com/HelloClyde/BBK9588-sango)。
`main` 用于源码和构建验证；首个发行版本计划为 `v0.1.0-alpha.1`，目前尚未推送版本标签或发布 Release。

1. 核对 `VERSION`、固定 `sdk` gitlink 和源码／素材的许可声明。
2. 干净检出只初始化 `sdk` 本身，不递归获取 SDK 的模拟器大型子模块。
3. 按 README 安装 Pillow、构建、打包、逐文件校验。发布 BDA 和 LIB 必须分别匹配 `validation/reference-build.json`。
4. 源码更新推送 `main`。发行版本另行确认后，再创建和推送与版本相符的标签。
5. 标签触发 CI，构建 job 保持只读权限。普通 push/PR/手动构建只上传临时 artifacts。
6. 发布 job 单独取得 `contents: write`，下载同一次构建的归档，校验其中每个文件，再创建预发布 Release。
   不重新编译、不覆盖既有 Release 或同名资产。仅推送标签不代表发布完成。

Actions 已从官方仓库核对当前接口，并固定到提交：checkout v7.0.1、setup-python v7.1.0、
upload-artifact v7.0.2、download-artifact v8.0.2。
上传显式使用 `archive: true`，下载显式解包并验证 digest；它们的传输归档摘要不当作 BDA 的 SHA-256。
最终逐文件校验以发行目录的 `SHA256SUMS.txt` 为准。

正常构建直接读取仓库中的解包资源和新增目标 PNG，不需要另外提供原版 BDA、LIB、固件、NAND、系统字库转储或个人存档。
升级包包含新版程序及 `应用/数据/游戏/sango.lib`；发行目录同时提供独立 `sango.lib`。
CI先检查89项资源用途的代码依据及命名，再运行10项资源回包检查，并校验BDA、LIB、ZIP内资源和逐文件哈希。
当前源文件包含原游戏恢复代码及初始化数据，许可缺项见根目录声明，不可擅自改成整仓 MIT。

预发布说明位于 `releases/v0.1.0-alpha.1.md`。实际发布后应核对 tag 提交、对应 Actions run、
Release 资产名称及大小，并下载成品重新验证文件哈希。
