# half_plane_intersection 驗證紀錄

[題目](statement/statement.md) · [作者備註](statement/author-notes.md)

此為原始 `Geometry/half_plane_intersection.hpp` 的有界、具有嚴格內點版本。完整分類題已移到 [half_plane_intersection_general](../half_plane_intersection_general/statement/statement.md)，仍為草稿，這次沒有為一般版產生 package。

## 規模與結果

- ICPC tmt package，時限 2 秒、記憶體 512 MiB。
- 28 筆資料（含兩筆範例），輸入與答案共 26,313,372 bytes（25.094 MiB），低於 64 MiB 預算。
- 單份程式筆數 × 時限為 56 秒；參考解加 7 份錯解的基礎額度為 448 秒，不含編譯、生成與評測器的額外 wall-time 係數。
- 本機參考解最慢一筆 0.039 秒，僅為本機量測。
- `gen`、參考解 `invoke` 與完整 `verify` 均成功，最終摘要 **0 warning, 0 error**。
- 參考解 28 筆全部 Accepted；6 份錯解各至少一筆 WA，gift wrapping 錯解三筆 TLE，其餘 25 筆 AC。

| 錯解 | 實際預期結果 | 一筆反例 |
|---|---|---|
| `loose-parallel.cpp` | WA | `1-samples-1` |
| `keep-collinear.cpp` | WA | `1-samples-1` |
| `narrow-turn.cpp` | WA | `2-coverage-09` |
| `float-turn.cpp` | WA | `2-coverage-16` |
| `input-order.cpp` | WA | `1-samples-1` |
| `reversed.cpp` | WA | `1-samples-1` |
| `gift-wrap.cpp` | TLE | `2-coverage-17` |

## 獨立性與額外核對

參考解使用精確整數齊次座標表示的極對偶凸包，時間 O(n log n)、空間 O(n)；未引用、複製或呼叫原始模板及 general 版本。

- 100 組固定種子小型案例，以 Python Fraction 從正方形逐次裁切，核對完整有效邊界及循環順序。
- 14 筆正式小型資料另通過同一精確裁切核對。
- 格點凸多邊形由依角度排序的 primitive 整數邊向量累積構造；逐一核對其全部有效支撐線。`2-coverage-16` 有 1,024 條真正邊界，`2-coverage-17`、`2-coverage-18`、`2-coverage-25` 各有 48,000 條；最後一筆已放大至 10^9 座標範圍。
- checker 11 組直接測試通過：正確答案、合法循環位移及重合代表接受；反序、重複邊、漏邊、額外頂點切線、較鬆平行線、多餘／不足 token、非法編號均拒絕。
- validator 的 7 組非法輸入均拒絕，涵蓋 n 超界、零方向、錯誤外框、原點在邊界／右側、座標超界及額外內容；兩組原始範例均接受。

## 值域擴充至 10^9

- 更動前執行 `gen --verify-hash`，結果 Hash matches；原 24 筆輸入與答案逐檔確認完全相同。
- 新增 4 筆：10^9 範圍隨機大案例、狹窄交集、放大格點凸多邊形、可用有理數核對的小型大座標案例；新 hash 已重建。
- 參考解以 UBSan 執行全部 28 筆正式資料並經 checker 接受，沒有偵測到整數溢位。
- Validator 接受 B 與座標恰為 10^9 的案例，拒絕 B = 10^9 + 1 與端點座標超界。
- 叉積可用 8C² 作保守上界，原模板交叉乘積至多 64C⁴；C = 10^9 時為 6.4×10^37。參考解齊次行列式各單項絕對值總和至多 48C⁴ = 4.8×10^37。兩者都小於 signed __int128 上限約 1.7×10^38；乘法必須先加寬。
- 修改前 package 與原 hash 備份：`/tmp/hpi-range-before-00be23rf`。未修改參考解演算法、checker、library、general 題目或任何 driver。

## 重建

在本 package 目錄執行：

```sh
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never gen -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never invoke solutions/sol.cpp -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never verify
```

include/ 已複製 ICPC 版 testlib/jngen，不依賴本機 symlink。錯解共用獨立 solver 的不同錯誤分支，checker 以輸入支撐線等價類精確比對，接受任意合法重合代表及循環起點。

## 保留與交接

原簡單版題面及每題作者備註已從備份還原；本次依使用者要求，將座標與 B 上限由 10^6 提高至 10^9，並補充中間乘積上界說明，其餘題目合約不變。現有一般版題目目錄改名為 `half_plane_intersection_general`，僅更新其目標 header／函式標示。更名前備份為 `/tmp/hpi-package-before-fbthxt72`。

所有既有 library、`.test.cpp` 與 CI 均未修改，也沒有新增 driver。Package 自身已驗證；原始半平面交模板仍待使用者撰寫 `.test.cpp` 後，再以本題測試。本次未執行原模板或 general 模板。
