# GitAlias
因为 Markdown 的文本性质，可以借助 git 实现极为优雅的多端同步。

虽然携带的图片资源也可以上传下载，但 Markdown 文本格式支持冲突合并，以及修改回退等操作。

这里记录了我正在使用的多端同步指令配置，支持如下功能：

- `t` 表示 Typora ，进入本地 Typora 工作目录（更改为你自己的仓库路径）
- `tpl` 表示 Typora pull ，下载并尝试合并
- `tps` 表示 Typora push ，下载并尝试合并，然后上传
- `tp` 等同于 `tps`

在使用 git pull 之前，请先设置远端仓库地址，我使用了 GitHub 的私有库，感谢微软。

这些功能使用指令 alias 简化了一些 git 指令，但对于不能自动 merge 的修改，需要自行解决冲突。

## On Unix-like Systems 
下面的内容放入 ~/.bash_profile

```
# Typora alias
alias t="cd ~/Desktop/Typora/" #change to your path
alias tpl="t ; git pull"
alias tps="tpl ; git add * ; git commit -m 'mac sync' ; git push" #change the message to yours
alias tp="tps"
```

## On Windows
在 Windows 系统下，使用 PowerShell 工作。
如下指令获取配置文件位置：

```
echo $PROFILE
```

然后新建或修改上面指令打印出的这个文件：~\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1

加入如下内容：

```
function t {cd ~\Desktop\Typora}
function tpl {t ; git pull}
function tps {tpl ; git add * ; git commit -m "win sync" ; git push}
function tp {tps}
```

