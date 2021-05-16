# Typora Tools
- Typora upload & download with git alias
- Typora local image cleaner
- Typora markdown archiver

## Typora Git Alias
使用 alias 的 git 指令，简化 Typora 仓库多端同步流程。
[配置方法](./GitAlias.md)



## Typora Image Cleaner
用于Typora或者文本类型的本地未使用图片清理工具。

个人倾向于将图片保存在本地，以防止图片链接失效。经常写Typora会增删图片，而本地图片不会因为连接删除而被移除，日积月累会导致本地图片数量爆炸。为了可持续发展，开发了这个自用工具。

### Usage
```shell
tic
```

### Flow
1. 遍历 `dirPath/` 中的所有 .md 文件
2. 正则搜索和储存文本中所有的 `![](xxx.jpg)` 和 `<img src="xxx.png">` 图片名称引用到哈希表
3. 清除 `imgPath/` 中不在哈希表记录的图片

稍作修改也可以适应其他文档资源清理工作，不只限于 Markdown 和 Image ，也不只限于上面的正则模式。

### Notices
- 为了简化指令，可执行文件名为 tic 或 tic.exe ，代表 Typora Image Cleaner
- 请正确放置可执行文件（见后文“默认 Typora 仓库目录结构”），或者修改代码中的路径，具体查看 ImgCleaner.cpp
- 删除文件会直接删除，不会移入回收站，建议熟悉功能前先保留副本
- `imgPath/` 下文件检索并不是递归的，可以视情况改为 `recursive_directory_iterator` 递归查找文件
- 需要 C++17 filesystem



## Typora Archiver
实现类似 `mv a.md archived/a.md` 的功能，但是支持同时移动文件所引用的图片，这样就不会导致引用缺失。

因为归档功能对路径很敏感，所以很可能需要修改源码中的路径，具体查看 Archiver.cpp 中的参数。

### Usage
```shell
ta ../a.md ../b.md ../c.md
```

### Flow
1. 检查 .md 文件是否存在
2. 正则搜索和储存文本中所有的 `![](xxx.jpg)` 和 `<img src="xxx.png">` 图片名称引用到哈希表
3. 移动所有 .md 到目标文件夹 `../archived/`
4. 移动所有 img 到目标文件夹 `../archived/assets/`

### Notices
- 为了简化指令，可执行文件名为 ta 或 ta.exe ，代表 Typora Archiver
- 请正确放置可执行文件（见后文“默认 Typora 仓库目录结构”），或者修改代码中的路径，具体查看 Archiver.cpp
- 不能解决多个文件引用相同图片的移动问题
- 需要 C++17 filesystem

## 默认 Typora 仓库目录结构
如果按照如下格式整理 Typora 仓库，则 tic 和 ta 都可以完美执行 Usage 中的指令。

```
.
├── LOG-202101.md
├── LOG-202102.md
├── LOG-202103.md
├── LOG-202104.md
├── LOG-202105.md
├── TEMP.md
├── TODO.md
├── archived
│   ├── LOG-202006.md
│   ├── LOG-202007.md
│   ├── LOG-202008.md
│   ├── LOG-202009.md
│   ├── LOG-202012.md
│   └── assets
│       ├── image-20200625153306463.png
│       ├── image-20200703133854250.png
│       ├── image-20200709172107899.png
│       └── image-20200715234140859.png
├── assets
│   ├── image-20210510170838463.png
│   ├── image-20210512181423133.png
│   ├── image-20210512181858079.png
│   ├── image-20210512182107335.png
│   ├── image-20210512182353821.png
│   ├── image-20210512190727619.png
│   ├── image-20210512191014058.png
│   ├── image-20210512191344911.png
│   ├── image-20210512234720149.png
│   └── image-20210512235453251.png
└── tools
    ├── Archiver.cpp
    ├── Archiver.h
    ├── CMakeLists.txt
    ├── ImgCleaner.cpp
    ├── ImgCleaner.h
    ├── ta
    └── tic
```
