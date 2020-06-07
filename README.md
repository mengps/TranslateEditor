# TranslateEditor

  Qt语言家(Qml版)

  提供更加简洁/清晰/实用的UI (自我感觉良好Ծ‸ Ծ)

  极易上手，so，可以给翻译人员使用

---

### 效果预览 [GIF 22.3MB]

![Image text](preview/preview.gif) 

---

### 构建

```
   TranslateEditor是完整的项目
   
   因此，直接构建即可

   要保证 [Qt version >= 5.13]
```

或者: 

```sh
   qmake TranslateEditor.pro

   make -f Makefile

```

--- 

### 使用方法

1. 打开 `.ts` 文件 [由lupdate.exe生成]
2. 填写翻译文本( Translate Text ) & 注释文本( Comment Text )
3. 设置 [Qt/lrelease.exe] 位置(若有环境变量则无需设置)，通常在 `[Qt目录]/[Qt Version]/[Kit]/bin` 目录下
```
 提示：更好的方式是将 lrelease.exe 复制到执行目录下，最后打包到一起，这样就无需 [Step 3]
```
4. 生成 `.qm` 文件

---

### 许可证

   使用 `Apache License 2.0`

--- 

### 开发环境

  Windows 10，Qt 5.13.0 [>= 5.13]

---

### 开发状态

`[偶尔维护...]`