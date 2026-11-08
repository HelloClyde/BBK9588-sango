# 启动图标：左下曹操与整面背景旗帜

以[原32×32图标](9288s-icon-original.png)及[无插值放大参考](9288s-icon-reference-zoom.png)为构图依据；放大参考与用户再次提供的图片逐像素相同。

当前构图按用户确认还原：

- 曹操位于左下角，脸朝右，没有金冠。
- 一整面旗帜填满人物后方的上方及右侧背景。
- 旗上只露出部分“曹”字，其余被头像及画面边缘遮住。
- 不使用此前误加的独立小旗、云纹或回纹边饰。
- 按用户圈选移除右侧孤立黑色笔画，以连续的旗布纹理和褶皱补齐。

[当前GPT Image母图](icon-gpt-image-master.png)、[局部清理提示词](imagegen-prompt.txt)、[构图还原提示词](imagegen-prompt-composition.txt)均入库；[去除黑块前的构图](icon-gpt-image-master-before-ink-removal.png)也保留。此前的[旧母图](icon-gpt-image-master-before-flag.png)、[旧提示词](imagegen-prompt-before-flag.txt)，以及未采用的[小旗草稿](icon-gpt-image-master-small-flag-draft.png)与[草稿提示词](imagegen-prompt-small-flag-draft.txt)保留供对照，不用于新版打包。

通过SDK固定图标规格输出四张PNG：`icon-0-80x80.png`、`icon-1-80x80.png`、`icon-2-54x54.png`、`icon-3-58x58.png`。程序构建使用SDK VX RGB565编码，图标位于BDA头部；本次不修改游戏内LIB、CLR或执行载荷。

```powershell
python tools/pack_app_icon.py
python build.py
python tools/package_release.py --require-validated
```

图形编辑使用内置GPT Image；脚本只将已保存母图转换到SDK要求的尺寸。四张图标的BDA像素/尺寸、SDK静态检查及载荷一致性见[验证记录](../../validation/app-icon-validation.json)。构图与参考细节由视觉核对，本次未宣称真机启动器验证。
