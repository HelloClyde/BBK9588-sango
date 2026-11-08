# sango.lib 可编辑资源

原文件名是 `sango.LIB`，设备程序使用 `sango.lib` 路径。它们在目标文件系统中是同名文件。
工具和构建产物统一写作 **`sango.lib`**，没有改名为 `sanguo.lib`。

原库：439720 字节，SHA-256
`42920210b5a130781ed1f1cce4bdaca3fc1bb95f14fac8d88d170a9ad77490a5`。
索引有 116 个槽位，87 条原资源。完整回包保留索引空槽、原始排列、间隙、遮罩保留位及行尾填充。
未修改素材时，`--original-only` 的输出与原文件逐字节相同。

## 修改和打包

在仓库根目录运行：

```powershell
python -m pip install -r requirements-assets.txt
python tools/sango_lib.py pack
```

默认读取本目录 `manifest.json`，输出 **`build/sango.lib`**。包含原资源与补充的 17、18 号资源，
当前为 461116 字节。可指定源目录、输出目录：

```powershell
python tools/sango_lib.py pack assets/library -o build/sango.lib
python tools/sango_lib.py pack --original-only -o build/sango-original.lib
python tools/sango_lib.py inspect build/sango.lib
python tools/test_sango_lib.py
```

`--original-only` 只排除补充条目，仍然会应用对原 PNG、动画或地图的修改；它不是“撤销修改”。
需要重新解包其他文件时，指定一个尚不存在的输出目录，工具不会覆盖已有编辑：

```powershell
python tools/sango_lib.py unpack PATH/TO/sango.lib -o build/library-inspection
```

完整构建 `python build.py` 自动打包 LIB 并同步新增素材的 C include；无需手动执行生成步骤。
安装包由 `tools/package_release.py` 生成，资源目标路径是 `应用/数据/游戏/sango.lib`。

## 文件对应

- `manifest.json`：资源 ID、类型、原位置/校验和、帧路径、原始物理顺序和补充资源，是打包入口。
- `rNNNN/record.bin`：每条原资源的完整种子数据。用于保留头部、原始数据、遮罩保留位及行尾填充。
  **不是缓存，必须随源码保存**。不要只复制 PNG 后删除它。
- `image-frame-NNN.png`：普通位图的所有帧，包括重复头像及字模；没有合并或删帧。
- `image-NNN-frame-000.png` 与 `timeline.json`：19 组动画的图像和指令，逐项保留顺序。
  每条动画指令是原始 5 字节数组；未将尚不明确的字段伪命名。
- `r0110`～`r0116/map.json`：7 张 32×32 战场地图，包含宽高与 tile ID 矩阵；其余头字段从种子保留。
- 文字、数据库及 100～107 号特殊地图布局等尚未语义解码的 32 条资源作为 `raw` 保存，回包原样写入。
  **没有把任意二进制误当作已恢复文本或图片**。

29 条普通位图和 19 组动画共导出 **1186 张 PNG**。地图不计入图像帧数。
PNG 只能使用 RGB `(0,0,0)`、`(85,85,85)`、`(170,170,170)`、`(255,255,255)`；
带遮罩的素材使用 alpha 0/255。保持目标尺寸、帧数和帧序。
透明像素下面的 RGB 也予以保留；任意中间灰度、彩色或半透明像素会明确报错，不自动有损转换。

补充条目引用上级目录的目标 PNG，不再维护另一份副本：

| ID | 内容 | 源图 | 尺寸 |
| --- | --- | --- | --- |
| 17 | 信息／查找底栏 | `../statusbar/toolbar-240x36.png` | 240×36 |
| 18 | 制作群组 | `../credits/credits-240x320.png` | 240×320 |

这两个原来空闲的索引槽位指向文件尾追加的数据；原来 87 条资源的位置和内容均保持一致。
当前 C 内嵌素材的生成关系见 [素材入口](../README.md)。

## 格式范围

索引项为小端 uint32 文件偏移，0/0xffffffff 表示空槽。
每条记录以 12 字节 `<IHHHH>` 头开始：总长度、资源 ID、条目数、固定步长、编码标记。
普通位图头为 `<HHBB>`：宽、高、帧数、标志；像素每字节 4 个，最高两位在左，行步长 `(width+3)//4`。
颜色值 0 白、1 浅灰、2 深灰、3 黑。标志低位为 1 时，每帧先遮罩平面再颜色平面；
9588 遮罩的每个两位组中低位 1 表示透明。工具保留未使用的高位及不足四像素的行尾位。
9288S 的遮罩极性不同，本工具面向这里的 **9588 LIB**，不接受整份 9288S EXE。

原素材并未提供新的开源授权，详见根目录来源与许可声明。
