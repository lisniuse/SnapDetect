# SnapDetect

一个基于 C++ 和 OpenCV 的 Windows 屏幕截图与模板匹配工具。

## 📋 项目简介

SnapDetect 是一个简单而高效的计算机视觉项目，可以自动截取 Windows 桌面屏幕，并在屏幕中寻找指定的模板图像。该项目使用 Windows GDI API 进行屏幕截图，使用 OpenCV 库进行图像处理和模板匹配。

## ✨ 功能特性

- 🖥️ **全屏截图** - 使用 Windows API 捕获整个桌面
- 🔍 **模板匹配** - 在屏幕截图中寻找指定的模板图像
- 📊 **匹配评分** - 显示匹配的置信度分数和位置坐标
- 🎯 **可视化结果** - 在匹配位置绘制绿色矩形框
- ⚡ **自动化编译** - 提供 PowerShell 脚本一键编译
- 🧹 **智能清理** - 自动管理编译产物和依赖库

## 🛠️ 环境要求

### 必需软件
- **操作系统**：Windows 10/11 (x64)
- **编译器**：Visual Studio 2022 Community (或更高版本)
- **OpenCV**：4.11.0 (需要自行下载)

### 硬件要求
- 至少 4GB RAM
- 500MB 磁盘空间

## 📥 安装步骤

### 1. 克隆项目
```bash
git clone https://github.com/your-username/SnapDetect.git
cd SnapDetect
```

### 2. 下载并准备 OpenCV 库

> **⚠️ 重要提示：** 由于 OpenCV 库文件较大（约500MB），本项目**不包含** OpenCV 预编译文件，需要您自行下载。

#### 下载 OpenCV
1. 访问 [OpenCV 官方发布页面](https://opencv.org/releases/)
2. 下载 **OpenCV 4.11.0** Windows 版本
3. 或直接下载：[opencv-4.11.0-windows.exe](https://github.com/opencv/opencv/releases/download/4.11.0/opencv-4.11.0-windows.exe)

#### 解压和配置
1. 运行下载的 `.exe` 文件，解压到任意目录（如 `C:\opencv`）
2. 将解压后的文件复制到项目的 `vector/opencv/` 目录
3. 确保目录结构如下：

```
vector/
└── opencv/
    ├── build/
    │   ├── include/
    │   └── x64/vc16/
    │       ├── lib/
    │       │   └── opencv_world4110.lib
    │       └── bin/
    │           └── opencv_world4110.dll
    └── sources/
```

### 3. 准备模板图像
在项目根目录放置一个名为 `template.png` 的图像文件作为匹配模板。

## 🚀 使用方法

### 编译项目
使用 PowerShell 运行编译脚本：
```powershell
.\build.ps1
```

### 运行程序
```powershell
.\bin\SnapDetect.exe
```

### 程序输出示例
```
Screenshot size: [1920 x 1080] channels: 3
Template size: [100 x 50] channels: 3
Best match at: [856, 234] with score: 0.891234
```

## 📁 项目结构

```
SnapDetect/
├── src/
│   └── main.cpp           # 主程序源代码
├── bin/                   # 编译输出目录 (自动生成)
│   ├── SnapDetect.exe     # 可执行文件
│   ├── opencv_world4110.dll
│   └── ...                # 其他编译产物
├── vector/
│   └── opencv/            # OpenCV 库文件 (需要自行下载)
├── build.ps1              # 自动编译脚本
├── .gitignore             # Git 忽略文件
├── README.md              # 项目文档
└── template.png           # 模板图像 (需要用户提供)
```

## 🔧 编译说明

### 自动编译 (推荐)
```powershell
.\build.ps1
```

### 手动编译
如果需要手动编译，可以参考以下命令：
```cmd
cl.exe src\main.cpp /I vector\opencv\build\include /EHsc /MD /Zi /Od /Fe bin\SnapDetect.exe /Fo bin\main.obj /Fd bin\vc140.pdb /link vector\opencv\build\x64\vc16\lib\opencv_world4110.lib gdi32.lib user32.lib
```

### 编译脚本功能
- ✅ 自动清理旧的编译产物
- ✅ 检查 Visual Studio 环境
- ✅ 编译源代码到 `bin` 目录
- ✅ 自动复制 OpenCV DLL 文件
- ✅ 错误检查和状态报告

## ⚠️ 注意事项

1. **OpenCV 库**：必须自行下载 OpenCV 4.11.0 并放置到正确目录
2. **模板图像**：确保 `template.png` 存在且为有效的图像文件
3. **Visual Studio**：需要安装 Visual Studio 2022 的 C++ 工具
4. **OpenCV 版本**：项目针对 OpenCV 4.11.0 配置，其他版本可能需要调整
5. **权限**：程序需要屏幕截图权限，某些安全软件可能会拦截

## 🐛 常见问题

### Q: 编译时提示找不到 OpenCV 库文件
**A:** 检查以下步骤：
1. 确认已下载 OpenCV 4.11.0
2. 检查 `vector/opencv/build/x64/vc16/lib/` 目录是否存在 `opencv_world4110.lib` 文件
3. 确认目录结构正确

### Q: 运行时提示找不到 DLL 文件
**A:** 编译脚本会自动复制 DLL，如果仍有问题：
1. 检查 `vector/opencv/build/x64/vc16/bin/` 目录是否存在 `opencv_world4110.dll`
2. 手动复制该文件到 `bin` 目录

### Q: 模板匹配效果不好
**A:** 尝试以下方法：
- 使用更清晰的模板图像
- 确保模板图像与屏幕内容尺寸相近
- 调整匹配算法参数

## 📄 许可证

本项目采用 MIT 许可证，详见 LICENSE 文件。

## 🤝 贡献

欢迎提交 Issue 和 Pull Request 来改进这个项目！

## 📧 联系方式

如有问题或建议，请通过 GitHub Issues 联系。
