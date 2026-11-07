# polygon-cover 驗證紀錄

[題目敘述](statement/statement.md) · [作者備註](statement/author-notes.md)

由 polygon-union 改為輸出至少被 1 到 k 個多邊形覆蓋的面積；k = 0 不輸出數值。原輸入條件、validator、範例輸入與 32 筆既有輸入保留，新增兩筆高層覆蓋與反向共邊資料。題面、參考解、checker、錯解及答案已同步更新。

## 資料與資源

- 正式資料 34 筆（含兩筆範例）。
- `.in` + `.ans` 共 46,978 bytes，低於 8 MiB 預算。
- 時限 1 秒，記憶體 512 MiB；筆數 × 時限為 34 秒，僅為單份程式一輪的上限估算，不含編譯、生成與錯解。
- 本機參考解最慢一筆 0.014 秒，不代表其他評測機的時間。

## 實際執行

在本 package 目錄執行以下指令，全數成功；完整 verify 摘要為 **0 warning, 0 error**：

```sh
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never gen -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never invoke solutions/sol.cpp -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never verify
```

參考解 34 筆均 Accepted，7 份刻意錯解均得到預期 Wrong Answer：

| 錯解 | 一筆實際反例 |
|---|---|
| `sum-only.cpp` | `1-samples-1` |
| `pairwise-only.cpp` | `2-coverage-05` |
| `polygon-boxes.cpp` | `1-samples-2` |
| `integer-area.cpp` | `2-coverage-02` |
| `exact-only.cpp` | `1-samples-1` |
| `suffix-sum.cpp` | `1-samples-1` |
| `union-only.cpp` | `1-samples-1` |

原 package 在修改前執行 `gen --verify-hash`，結果 Hash matches。此次輸出合約已改變，所有答案與新 hash 均依新規格重建。原始備份位於 `/tmp/polygon-cover-before-43sp1w4r`，包括舊答案；目錄改名留下的編譯快取已移開重建。

## 獨立交叉檢查

參考解採垂直分帶，未引用或複製目標 library。

- 60 組固定種子小型三角形／重複圖形，每個覆蓋層數均與 Fraction 精確有理數比對，要求誤差不超過 10^(-9) × max(1, |答案|)。
- 11 筆正式資料的所有層數另以有理數核對，包含兩組範例、空集合、分數面積、洞、相切／共邊、近乎平行、60 層重複與兩側堆疊。
- 14 筆正式矩形資料另以整數座標壓縮精確核對。
- checker 12 組直接測試通過：各層誤差內外、NaN／無窮大、缺 token、多 token、k = 0 的空白輸出與非法數值。

## Library 與使用者 driver

`Geometry/polygon.hpp` 新增 `polyCoverArea`；`polyUnionArea` 保留為回傳第一層的相容函式，空集合回傳 0。舊 Codeforces driver 已確認仍可編譯。

Library 額外以獨立分帶參考法核對 600 組隨機／排列案例及 7 組固定案例，同時檢查預設 double 與 long double 結果、單調性、各層面積總和等於輸入面積總和。固定案例包含空集合、單一圖形、60 個相同圖形、反向部分共邊、分數面積、近乎平行與大座標平移；ASan、UBSan 均通過。

這些是函式層級回歸檢查，尚未透過使用者新版 driver 跑正式題目。既有 `polygon-union.test.cpp` 只隨目錄搬移，內容與檔名不變；其中 PROBLEM 與輸出格式仍需由使用者自行改為 polygon-cover。沒有新增 `.test.cpp`，也沒有修改 CI。
