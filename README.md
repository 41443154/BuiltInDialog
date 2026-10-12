# BuiltInDialog — Qt 內建對話框展示程式

使用 **C++、Qt Widgets 與 CMake** 製作的 Windows 桌面程式，展示 Qt 常見的內建對話框及文字編輯功能。

> 本 README 同時記錄「**原始碼上傳 GitHub → Release 編譯 → Windows 打包 → 發布 GitHub Releases**」的完整流程。

## 專案資訊

| 項目 | 內容 |
| --- | --- |
| 專案名稱 | BuiltInDialog |
| 開發語言 | C++17 |
| GUI 框架 | Qt Widgets / Qt PrintSupport |
| Qt 版本 | 6.11.2（本專案開發環境） |
| 編譯器 | MinGW-w64 64-bit（本專案使用 `mingw1310_64`） |
| 建置工具 | CMake |
| 主要平台 | Windows 64-bit |
| 原始碼 | [GitHub Repository](https://github.com/41443154/BuiltInDialog) |
| Windows 下載 | [GitHub Releases](https://github.com/41443154/BuiltInDialog/releases) |

## 功能展示

| 功能 | 說明 |
| --- | --- |
| 顏色對話框 | 選擇 `QTextEdit` 的背景顏色 |
| 更改文字顏色 | 開啟顏色選擇器，將選定顏色套用到編輯框中的文字 |
| 錯誤訊息框 | 展示 `QErrorMessage` |
| 檔案對話框 | 選取檔案，將**檔案路徑**顯示在文字框中（不讀取檔案內容） |
| 字體對話框 | 選擇字型與大小 |
| 輸入對話框 | 輸入文字並顯示在文字框中 |
| 頁面設定對話框 | 展示紙張與頁面設定；目前設定不會保存至下次列印 |
| 進度對話框 | 以迴圈**模擬**工作進度，支援取消；不會真正複製檔案 |
| 列印對話框 | 選擇印表機，列印 `QTextEdit` 內容 |

## 專案檔案

```text
BuiltInDialog/
├── CMakeLists.txt
├── main.cpp
├── cbuildindlg.cpp
├── cbuildindlg.h
└── README.md
```

> `build/`、`.qtcreator/`、`*.user`、`CMakeCache.txt`、`Makefile` 等本機產生的設定或編譯檔，通常**不要上傳到原始碼儲存庫**。打包好的 Windows 執行版本放在 **Releases**，而不是直接提交大量 DLL 到 `main` 分支。

---

# 一、第一次將原始碼上傳 GitHub

1. 登入 [GitHub](https://github.com)，開啟 [New repository](https://github.com/new)。
2. Repository name 輸入 `BuiltInDialog`，Visibility 選擇 `Public`，建立儲存庫。
3. 在 Windows 檔案總管開啟本機 Qt 專案資料夾。本專案開發時使用：

   ```text
   %USERPROFILE%\Desktop\HD\BuiltInDialog
   ```

4. 在 GitHub 儲存庫首頁選擇 **Add file → Upload files**。
5. 上傳 `CMakeLists.txt`、`main.cpp`、`cbuildindlg.cpp`、`cbuildindlg.h` 等原始碼檔案，並加入這份 `README.md`。
6. Commit message 可填 `Upload Qt BuiltInDialog source code`，再按 **Commit changes**。
7. 返回儲存庫首頁，確認所有原始碼檔案都在 `main` 分支。

**更新已存在的 README：** 在 GitHub 開啟 `README.md`，點擊右上角的鉛筆圖示（**Edit this file**），貼上新內容，然後按 **Commit changes**。不必另外建立第二份 README。

# 二、使用 Qt Creator 編譯 Release 版本

> 以下依據本專案使用的 **Qt 6.11.2 + MinGW 64-bit + CMake** 環境說明。其他使用者請依其 Qt 安裝版本調整路徑。

1. 開啟 Qt Creator，選擇專案內的 `CMakeLists.txt`。
2. 確認使用 **Desktop Qt 6.11.2 MinGW 64-bit** Kit。
3. 進入 **Projects（專案）→ Build Settings（建置設定）**。
4. 在 **Active build configuration** 下拉選單選擇 `Release`；若尚未建立，點擊旁邊的 **新增**，建立獨立的 Release 組態。
5. 確認 **Build type** 和 `CMAKE_BUILD_TYPE` 均顯示 `Release`。
6. 按 **Ctrl + B** 編譯，確認「建置成功」。
7. 在 Build Settings 中查看 **Build directory**，找到編譯產生的 `BuiltInDialog.exe`。

在本專案目前的設定下，Release 輸出目錄通常是：

```text
%USERPROFILE%\Desktop\HD\BuiltInDialog\build\Desktop_Qt_6_11_2_MinGW_64_bit_Release
```

> `Debug` 和 `Release` 應使用**不同**的建置目錄，避免 CMake 快取互相干擾。

# 三、打包 Windows EXE 與 Qt 相依檔案

Qt 程式通常不能只提供單一 `.exe`，因為其他電腦可能缺少 Qt 的 DLL、平台插件或 MinGW 執行階段檔案。

## 1. 準備發布資料夾

1. 在 Windows 桌面建立 `BuiltInDialog-Windows` 資料夾。
2. 將上一節編譯成功的 **Release 版** `BuiltInDialog.exe` **複製**進去。
3. 確認資料夾暫時包含：

   ```text
   BuiltInDialog-Windows/
   └── BuiltInDialog.exe
   ```

## 2. 使用 `windeployqt`

按 **Win + R**，輸入 `cmd` 並按 Enter。在 **同一個命令提示字元視窗**，依序執行以下命令：

```bat
call "C:\Qt\6.11.2\mingw_64\bin\qtenv2.bat"
set "PATH=C:\Qt\Tools\mingw1310_64\bin;%PATH%"
"C:\Qt\6.11.2\mingw_64\bin\windeployqt.exe" --release --compiler-runtime "%USERPROFILE%\Desktop\BuiltInDialog-Windows\BuiltInDialog.exe"
```

- `qtenv2.bat`：設定 Qt 執行環境。
- `set PATH=...`：讓工具找到本專案使用的 MinGW 編譯器執行階段。
- `windeployqt --release --compiler-runtime`：將偵測到的 Qt DLL、平台插件及編譯器執行階段部署到 EXE 所在資料夾。
- 如果 Qt 不在 `C:\Qt`，請依實際安裝路徑修改命令。

成功後可能看到類似結構（實際檔案依部署結果而定）：

```text
BuiltInDialog-Windows/
├── BuiltInDialog.exe
├── Qt6Core.dll
├── Qt6Gui.dll
├── Qt6Widgets.dll
├── Qt6PrintSupport.dll
├── platforms/
│   └── qwindows.dll
└── 其他相依 DLL 與資料夾
```

> `windeployqt` 不能保證打包所有**非 Qt 第三方函式庫**。如日後加入其他函式庫，需要自行檢查其相依檔案與散布授權。

## 3. 測試與壓縮

1. 在 `BuiltInDialog-Windows` 資料夾內直接執行 `BuiltInDialog.exe`。
2. 測試各個按鈕，尤其是顏色、輸入、字體、列印等功能。
3. **最好再用一台沒有安裝 Qt Creator／Qt 的 Windows 64-bit 電腦測試**，確認沒有缺少 DLL 或平台插件。
4. 在 Windows 檔案總管，右鍵整個 `BuiltInDialog-Windows` 資料夾 → **壓縮成 ZIP 檔案**。
5. 將 ZIP 命名為：

   ```text
   BuiltInDialog-Windows-v1.0.0.zip
   ```

下載者必須**完整解壓縮** ZIP，再執行資料夾中的 EXE；不能只把 EXE 單獨移出。

# 四、將 ZIP 正式發布到 GitHub Releases

1. 開啟本專案的 [GitHub 儲存庫](https://github.com/41443154/BuiltInDialog)。
2. 進入 **Releases → Draft a new release**（或 **Create a new release**）。
3. 點擊 **Choose a tag**，輸入 `v1.0.0`，建立新標籤，Target 選擇 `main`。
4. **Release title** 填寫 `BuiltInDialog v1.0.0`。
5. **Description** 可填入：

   ```markdown
   ## BuiltInDialog v1.0.0

   第一個 Windows 64-bit 發布版本。

   - Qt 6 / C++ 內建對話框展示
   - 支援顏色、文字、字體、檔案選擇、進度與列印對話框

   ### 使用方式
   1. 下載 `BuiltInDialog-Windows-v1.0.0.zip`
   2. 完整解壓縮
   3. 執行 `BuiltInDialog.exe`
   ```

6. 找到附件上傳區（**Attach binaries**），將 `BuiltInDialog-Windows-v1.0.0.zip` 拖曳上傳。
7. 確認 ZIP 已完成上傳，發布正式版本時不要勾選 **This is a pre-release**；可勾選 **Set as latest release**。
8. 點擊 **Publish release**。
9. 開啟 [Releases](https://github.com/41443154/BuiltInDialog/releases)，在 **Assets** 確認可看到並下載 ZIP。

**注意：** GitHub 自動產生的 `Source code (zip)` 只是原始碼，**不等於**附有 DLL 的 Windows 執行版；一般使用者應下載自行上傳的 `BuiltInDialog-Windows-v1.0.0.zip`。

# 五、之後更新程式如何重新發布？

1. 在 Qt Creator 修改程式碼並確認功能正常。
2. 到 GitHub 更新變動的 `.cpp`、`.h`、`CMakeLists.txt` 或 README，提交新的 Commit。
3. 重新以 **Release** 組態編譯最新的 EXE。
4. 建議用**新的空白** `BuiltInDialog-Windows` 資料夾重新執行 `windeployqt`，避免舊版 DLL 混入。
5. 測試成功後，壓縮成 `BuiltInDialog-Windows-v1.0.1.zip`。
6. 在 GitHub 建立**新** Release，Tag 使用 `v1.0.1`，上傳對應 ZIP 並發布。

版本號可依更新規模調整，例如 `v1.0.1`（小修正）、`v1.1.0`（增加功能）、`v2.0.0`（重大變更）。

# 六、常見問題

**Q：執行 EXE 出現「找不到 Qt6Core.dll」怎麼辦？**  
A：確認有對 **Release EXE 所在的發布資料夾**執行 `windeployqt`，不要只單獨複製 EXE；必要時檢查 MinGW 執行階段是否被正確部署。

**Q：出現 `Could not find or load the Qt platform plugin "windows"`？**  
A：確認發布資料夾有 `platforms/qwindows.dll`，而且其版本和 EXE 所連結的 Qt 相容；不要混用 Debug、Release 或不同版本的 DLL。

**Q：搬動專案後出現 CMake cache source path 不一致？**  
A：在 Qt Creator 重新設定 CMake，或刪除**對應的 build 輸出資料夾**後重新建置；不要刪除 `CMakeLists.txt` 或 `.cpp`、`.h` 原始碼。

**Q：下載者需要 Qt Creator 嗎？**  
A：如果相依檔案打包正確，下載者通常不需要安裝 Qt Creator。但仍應在沒有安裝 Qt 的電腦上實際驗證。

**Q：為什麼不直接把 `build/` 上傳 GitHub？**  
A：建置資料含大量自動產物和本機路徑，通常無法跨電腦直接重用；原始碼保留在儲存庫，給使用者的打包版本則放在 Releases。

## 參考文件

- [Qt 官方：Windows 部署與 windeployqt](https://doc.qt.io/qt-6/windows-deployment.html)
- [GitHub 官方：新增檔案至儲存庫](https://docs.github.com/en/repositories/working-with-files/managing-files/adding-a-file-to-a-repository)
- [GitHub 官方：建立及管理 Releases](https://docs.github.com/en/repositories/releasing-projects-on-github/managing-releases-in-a-repository)

> 本專案使用 Qt。公開散布 Windows 執行版本前，應確認 Qt 與其他相依函式庫所適用的授權及散布義務。此 README 不代表已替專案選定授權條款。
