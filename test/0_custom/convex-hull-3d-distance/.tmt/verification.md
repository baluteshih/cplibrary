# convex-hull-3d-distance 驗證紀錄

[題目](statement/statement.md) · [作者備註](statement/author-notes.md)

ICPC tmt package 已完成生成與驗證。題面與作者備註沿用核准版本，內容及修改時間均未變動。

## 實際結果與預算

- 正式測資 24 筆（含範例），輸入與答案合計 26,114,050 bytes（24.904 MiB）。
- 時限 3 秒、記憶體 512 MiB。筆數 × 時限為 72 秒，僅為單一程式一輪的上限估算；參考解加 7 份錯解的基礎額度為 576 秒，不含編譯、checker 或評測器 wall-time 係數。
- 本機參考解最慢單筆 0.140 秒，全資料逐筆時間總和約 0.492 秒；不含生成、編譯和 checker，也不代表使用者 driver 的時間。
- `gen`、參考解 `invoke`、完整 `verify` 均成功，最終摘要 **0 warning, 0 error**。
- 參考解全數 Accepted，以下 7 份錯解都得到預期失敗。

| 錯解 | 預期且實際得到 | 一筆反例 |
|---|---|---|
| `signed.cpp` | WA | `1-samples-1` |
| `no-normalization.cpp` | WA | `1-samples-1` |
| `squared-normalization.cpp` | WA | `1-samples-1` |
| `min-support.cpp` | WA | `1-samples-1` |
| `narrow-dot.cpp` | WA | `2-coverage-06` |
| `float.cpp` | WA | `1-samples-1` |
| `nearest-vertex.cpp` | WA | `1-samples-1` |

## 獨立核對

參考解不建立凸包：以 primitive 法向量快取全部輸入點的最大內積，再用精確整數分子與平方長度計算距離，最後才轉 long double。Validator 亦直接確認每個方向至少有三個不共線的最大內積點，拒絕只暴露一條邊或一個頂點的方向。

- 共 14,675 筆距離，以 Python 任意精度整數與 80 位 Decimal 平方根獨立核對；小型資料全查，較大資料採固定的分散索引。要求誤差 ≤ 10^(-12) × max(1,正解)，比正式 checker 更嚴格。
- 全部 24 筆正式資料用 UBSan 參考解重跑，輸出與答案相同，未偵測到溢位。
- Numeric checker 的 11 組直接測試通過：合法輸出與誤差內答案接受；逐筆誤差外答案、負值（即使絕對值小於容許誤差）、NaN／無窮大、缺／多 token 拒絕。
- Validator 的 7 組直接測試通過：有效面方向接受；只暴露頂點／邊、非 primitive、零向量、向量超界與查詢點超界拒絕。
- 高法向量四面體案例明確保證一筆距離的精確分子絕對值超過 2^63，實際攔截 narrow-dot.cpp。

## CI 資料預算

只有兩筆 q = 200 000 的資料；n 最大為 500。其他資料以平面兩側、平面上、垂足落在面外、重複點、共平面面片、大法向量與大座標相消的反例為主。參考解逐法向量掃點，與使用者預期的凸包 Face 查表流程獨立。


## 重建與交接

從本 package 目錄執行：

```sh
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never gen -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never invoke solutions/sol.cpp -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never verify
```

`include/` 已複製 ICPC 版 testlib/jngen，無本機 symlink 依賴。生成資料及編譯產物依 .gitignore 排除，testcases/hash.json 保存目前資料指紋。本次在只有 statement/ 的目錄新增 package，未覆蓋既有解答或題面。

所有既有 library、`.test.cpp` 與 CI 均未修改，也未新增 driver。參考解、generator、validator、checker 沒有呼叫被測 header。本紀錄表示 package ready；目標 library 是否通過與實際 CI 耗時，仍待使用者自行撰寫 driver 後再測。
