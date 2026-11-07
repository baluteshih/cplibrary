# polygon-containment 驗證紀錄

此 ICPC tmt package 已完成生成及驗證。題目與作者筆記位於 [statement/](statement/)，保留核准版本。

## 規模

- 測資：28 筆（含範例）。
- `.in` + `.ans`：3,792,624 bytes（3.617 MiB）。
- 每筆時限：3 秒；筆數 × 時限：84 秒（單一程式的一輪上限估算，不含編譯、生成與其他解答）。
- 本機參考解單筆最長實測：0.021 秒；此數值不代表其他評測機的執行時間。

## 實際驗證

於本 package 目錄執行下列三項，均成功；完整 `verify` 結果為 `0 warning, 0 error`：

```sh
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never gen -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never invoke solutions/sol.cpp -r
MAKE=gmake CXX=/opt/homebrew/bin/g++-16 LC_ALL=C python3 /Users/baluteshih/Project/tmt-cli/tmt.py --color never verify
```

參考解全數 Accepted；以下各刻意錯解均取得預期 Wrong Answer。表內列出至少一筆反例，完整執行紀錄由 tmt 留於本機 `logs/`。

| 錯解 | 反例 |
|---|---|
| `bbox-only.cpp` | `1-samples-1` |
| `boundary-inside.cpp` | `1-samples-1` |
| `boundary-outside.cpp` | `1-samples-1` |
| `ccw-only.cpp` | `2-coverage-04` |
| `double-vertex.cpp` | `2-coverage-05` |

全部 28 筆答案另以獨立整數射線奇偶判斷交叉核對。Validator 已確認拒絕重合的線段端點與自交多邊形。

## 使用界線

參考解獨立實作，未呼叫或複製目標 library。`include/` 內已複製 ICPC 版 testlib/jngen，無需依賴本機 symlink。生成檔與編譯產物依 `.gitignore` 排除，可用上述指令重建。

本流程沒有新增或修改任何 `.test.cpp`，也沒有修改 library 或 CI。這份紀錄證明 package 自身通過驗證；`Geometry/polygon.hpp` 的實際驗證仍待使用者撰寫 driver。
