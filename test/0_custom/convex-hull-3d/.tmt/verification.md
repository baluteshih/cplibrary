# convex-hull-3d 驗證紀錄

[題目](statement/statement.md) · [作者備註](statement/author-notes.md)

ICPC tmt package 已完成生成與驗證。題面與作者備註沿用核准版本，內容及修改時間均未變動。

## 實際結果與預算

- 正式測資 20 筆（含範例），輸入與答案合計 676,793 bytes（0.645 MiB）。
- 時限 3 秒、記憶體 512 MiB。筆數 × 時限為 60 秒，僅為單一程式一輪的上限估算；參考解加 7 份錯解的基礎額度為 480 秒，不含編譯、checker 或評測器 wall-time 係數。
- 本機參考解最慢單筆 0.121 秒，全資料逐筆時間總和約 0.424 秒；不含生成、編譯和 checker，也不代表使用者 driver 的時間。
- `gen`、參考解 `invoke`、完整 `verify` 均成功，最終摘要 **0 warning, 0 error**。
- 參考解全數 Accepted，以下 7 份錯解都得到預期失敗。

| 錯解 | 預期且實際得到 | 一筆反例 |
|---|---|---|
| `divide-six.cpp` | WA | `1-samples-1` |
| `narrow-volume.cpp` | WA | `2-coverage-01` |
| `triangle-count.cpp` | WA | `1-samples-2` |
| `flip-normal.cpp` | WA | `1-samples-1` |
| `unnormalized.cpp` | WA | `1-samples-1` |
| `first-four.cpp` | WA | `1-samples-1` |
| `cubic-pivot.cpp` | TLE | `2-coverage-15` |

## 獨立核對

參考解使用獨立的 3D gift wrapping，直接探索 maximal polygonal facets，未引用／複製目標的逐點可見三角面刪除法。

- 150 組固定種子小型點集（含重複點）及兩組範例，與獨立 O(n⁴) 支撐平面枚舉核對全部外向平面及六倍體積。
- 7 筆正式四面體／盒子／棱錐資料的面數與體積另以解析公式核對，包含 V_6 = 8×10^27、V_6 = 1 的極薄四面體、原點在外部的平移盒子。
- 全部 20 筆正式資料用 UBSan 參考解重跑，輸出與答案完全相同，未偵測到溢位。
- 精確 checker 的 11 組直接測試通過：正確輸出、超過 int64 的合法整數接受；錯體積、錯面、錯順序、反向平面、未約分、缺／多 token、錯誤整數與 int128 溢位字串拒絕。
- Validator 5 組直接測試通過：正常四面體、重複／共線起始的合法範例接受，非三維、座標超界與多餘內容拒絕。

## CI 與效能覆蓋

正式資料最多兩筆 n = 3 000，沒有 10 000 點壓測。格點拋物面與小幅擾動族保證所有點為凸包頂點，不能靠大量內部點讓逐面掃描近線性。三次複雜度錯解在 4 筆資料 TLE，其餘 16 筆 AC，證明此錯解確實被目前資料攔截；不等於已證明目標模板的漸近複雜度。

下表為本機**獨立參考解**的單筆時間，含評測程序啟動成本；尚未執行使用者模板。

| 案例 | n | 真正面數 | 參考解秒數 |
|---|---:|---:|---:|
| `2-coverage-13` | 500 | 479 | 0.010 |
| `2-coverage-14` | 1000 | 951 | 0.015 |
| `2-coverage-15` | 2000 | 1954 | 0.038 |
| `2-coverage-16` | 3000 | 2896 | 0.075 |
| `2-coverage-17` | 2000 | 3860 | 0.060 |
| `2-coverage-18` | 3000 | 5787 | 0.121 |

建構子與 polygon_face_num 都可能花二次時間。待使用者完成 driver 並另行要求量測後，才分別記錄兩階段耗時、記憶體及 time/n²；本 package 沒有強迫 driver 寫入計時輸出。


## 重建與交接

從本 package 目錄執行：

```sh
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never gen -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never invoke solutions/sol.cpp -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never verify
```

`include/` 已複製 ICPC 版 testlib/jngen，無本機 symlink 依賴。生成資料及編譯產物依 .gitignore 排除，testcases/hash.json 保存目前資料指紋。本次在只有 statement/ 的目錄新增 package，未覆蓋既有解答或題面。

所有既有 library、`.test.cpp` 與 CI 均未修改，也未新增 driver。參考解、generator、validator、checker 沒有呼叫被測 header。本紀錄表示 package ready；目標 library 是否通過與實際 CI 耗時，仍待使用者自行撰寫 driver 後再測。


## 後續使用者 driver 驗證

使用者已自行完成 driver，並要求進行對抗驗證。正式 20 筆、10,000 組額外對拍、精確枚舉抽查及 sanitizer 檢查均通過；完整方法、來源指紋與限制見 [hack-review.md](hack-review.md)。此更新不代表已證明完全不存在反例。
