# TyporaTools
- Typora local image cleaner
- Typora markdown archiver

## TyporaImageCleaner
用于Typora或者文本类型的本地未使用图片清理工具。

个人倾向于将图片保存在本地，以防止图片链接失效。经常写Typora会增删图片，而本地图片不会因为连接删除而被移除，日积月累会导致本地图片数量爆炸。为了可持续发展，开发了这个自用工具。

### Steps
1. 遍历 `dirPath/` 中的所有 `.md`
2. 正则搜索储存所有 `![](xxx.jpg)` 和 `<img src="xxx.png">` 图片名称引用到哈希表
3. 清除 `imgPath/` 中不在哈希表记录的图片

稍作修改也可以适应其他文档资源清理工作，不只限于 Markdown 和 Image ，也不只限于上面的正则模式。

### Notices
- 为了简化指令，可执行文件名为 tic 或 tic.exe ，代表 Typora Image Cleaner
- 删除文件会直接删除，不会移入回收站，建议熟悉功能前先保留副本
- `imgPath/` 下文件检索并不是递归的，可以视情况改为 `recursive_directory_iterator` 递归查找文件
- 需要 C++17 filesystem

## TyporaArchiver
TODO
