## v4.24.0

### 新增

- 新增领取邮件功能 (#6438) @broken-paint
- 肉鸽烧开水模式增加凹开局直升 (#6443) @Lancarus
- 肉鸽适配高规格分队开局 (#6436) @Lancarus
- 开始唤醒-账号切换新增手动切换，可单独执行开始唤醒流程 (#6433) @status102
- 如果任务流程中勾选了刷理智，则在任务链结束时提供一个理智回满的预测时间 (#6456) @status102
- macOS 国际服允许添加生息演算任务 @hguandl
- 自动战斗新增战斗列表选项（异形UI不支持） (#6350) @status102
- WPF自动战斗对于作业描述的视频自动跳转增加av号支持 (#6363) @status102
- 基建 制造站、贸易站、控制中枢 新增支持干员编组配置 (#6249) @status102
- 基建支持加工站 @MistEO
- 新增开始唤醒时账号切换功能 (官服、B服 only) (#6268) @status102
- 自动战斗-自动编队，新增自动补充低信赖干员、追加自定干员选项 (#6282) @status102
- 自动更新游戏资源而不用更新软件版本 (#6283) @MistEO
- 可自选日志日期显示格式 @ABA2396
- 新增复刻活动时，连续刷普通1-9关 (异形UI暂不支持，例如愚人号)，支持上报至企鹅物流 (#6230) @status102
- 增加刷理智每次打关卡之前时的理智剩余量输出 (#6146) @status102
- 支持 SideStory「不义之财」活动导航 & 添加 "SideStoryStage" 模板 roi @ABA2396
- shutdown/hibernate after all other MAAs have exited, or just exit itself (#6147) @Neptsun
- 添加CLI支持 (#6144) @wangl-cc
- 新增肉鸽干员自动撤退字段 (#6241) @AnnoyingFlowers
- 注册表查询bluestacks hyper-v的conf位置 (#6083) @Gliese129
- 支持woolang绑定 (#6142) @mrcino

### 改进

- 在非烧水模式，取消刷直升按钮 (#6484) @mole828
- optimize time diff format in sanity report (#6512) @KevinT3Hu
- 投资达到上限后退出到肉鸽主界面 (#6435) @zzyyyl
- 优化傀影招募策略 (#6476) @Lancarus
- 激活自动战斗-战斗列表时将同时激活自动编队，调整自动战斗UI (#6448) @status102
- 优化傀影肉鸽招募和商店逻辑 (#6447) @Lancarus
- 稍微优化下自动战斗界面 ui @moomiji
- 优化 自动战斗-战斗列表 跳过战斗后剧情的逻辑 (#6430) @status102
- 优化萨米招募逻辑 (#6422) @Lancarus
- 稍微优化下自动战斗界面 ui @ABA2396
- 水月肉鸽：增加支援道具，新干员分组，优化大君遗脉策略 (#6372) @Yumi0606
- 适配萨米肉鸽生活至上分队，优化部分逻辑 (#6385) @Lancarus
- 基建换班-干员编组增加可用干员缓存，同时在单次换班任务中避免重复匹配已匹配的干员 (#6376) @status102
- 下载更新资源先使用临时文件缓存 @MistEO
- 优化定时任务 @ABA2396
- 更新游戏资源时弹窗提示 @MistEO
- 增加未通过企鹅检查的掉落截图，增加 UnknownStage 时的难度回调 (#6308) @zzyyyl
- 优化自动战斗-自动编队-追加自定干员选项UI，当选项禁用时，居中CheckBox (#6322) @status102
- 优化萨米肉鸽策略 (#6288) (#6321) @Lancarus
- 优化刷理智的SSReopen导航逻辑，允许从普通关页面启动时短路开始于主页的导航逻辑 (#6287) @status102
- 优化萨米肉鸽策略 (#6266) @Lancarus
- 优化刷源石锭模式的逻辑，跳过战斗后招募，增加进入纵向节点的逻辑 (#6140) @Lancarus

### 修复

- 自动战斗跳过“以下干员出战后将被禁用，是否继续？”对话框 #4917 #4694 #5351 (#6492) @Hydrogina
- 自动战斗-自动编队-补充低信赖干员: 修正补充顺序，避免在极端情况下补充错误 (#6499) @status102
- 尝试修复肉鸽卡在招募界面 (#6516) @Lancarus
- 自动战斗-战斗列表，补充突袭结算图，修复从缓存文件夹添加作业时报错 (#6497) @status102
- 修复凹直升功能造成的卡在招募立绘等bug (#6502) @Lancarus
- 删掉多余的模板图片 @zzyyyl
- 增加延迟以提高刷理智-当前理智识别成功率 (#6402) @status102
- 修复 sanity_report == null 的问题 @zzyyyl
- 加工站不设置干员时，直接报错并返回 @MistEO
- 修复水月肉鸽卡在藏品 (#6464) @mole828
- 修复 debug 模式下 tasks.json 检查未通过时的访问越界问题 @zzyyyl
- 修复网络波动造成的使用理智药不清理智问题 @zzyyyl
- 修复自动战斗-战斗列表的导航失效问题 (#6413) @status102
- 修复Status缓存跨任务清理在任务链正常完成情况下失效的错误 (#6428) @status102
- 修复外部通知错误 (#6414) @LiamSho
- 修复资源读取错误，修复错误的界面提示 @ABA2396
- 修复资源更新toast笔误 @MistEO
- 通过进程名关闭蓝叠时如果模拟器个数超过1个则放弃关闭 @ABA2396
- 修复task.png阈值 @MistEO
- 修复SettingsView的Idle不生效，将开始唤醒-账号切换在非Idle情况下锁定 (#6364) @status102
- etag 解析报错 @ABA2396
- 将账号切换输出文本中的目标账号由输入文本改为OCR结果，尝试修复账号切换出错 (#6353) @status102
- 给关卡选择为 null 时打个补丁 @moomiji
- 更新文档 @Rbqwow @Black1312 @HisAtri
- 修复因部分皮肤造成的关卡难度识别问题 (#6309) @zzyyyl
- 修复肉鸽某些开局干员精二后首次进入关卡时不选三技能的问题 @AnnoyingFlowers
- 修复更新资源下载异常，及检查更新按钮过早亮起的问题 @MistEO
- 简单修复一下异步Load导致的错误 @MistEO
- Missing templates in EN @Constrat
- 修复连接安卓手机，及多开模拟器时，adb 端口判断异常 @MistEO
- 修复肉鸽招募卡住的问题 (#6528) @Lancarus
- 自动战斗-战斗列表启用时，对所有作业追加摆完挂机选项操作 (#6533) @status102
- 修复ProcessTask停不掉的问题 @MistEO
- 修改理智数据格式 (#6525) @zzyyyl @status102
- 继续尝试修复肉鸽卡在招募界面 (#6521) @Lancarus
- 修复萨米肉鸽关卡json“生人勿进”->"生人勿近" (#6262) @Lancarus
- 尝试修复网络波动造成的碎石不用问题 (#6220) @zzyyyl
- 修复萨米肉鸽作战关卡逻辑错误 (#6235) @mole828
- 萨米商店不识别第二排商品 (#6232) @Lancarus
- 修复肉鸽道中抓取干员 山 或 林 后重复开启技能的问题 (#6221) @AnnoyingFlowers
- regex for trader shopping in I.S. @Constrat
- 萨米boss关正则替换错误 (#6211) @Lancarus
- 麒麟X夜刀->麒麟R夜刀 (#6195) (#6199) @Constrat @SherkeyXD
- fix failing to choose rewards from the last run @178619
- 修复仓库识别无法在表格框内滚动 @ABA2396

### 其他

- 优化部分 WPF 代码 (#6510) @ABA2396 @zzyyyl
- 优化 wpf 代码 (#6504) @zzyyyl
- i18n: at on in date time @Constrat
- debug: debug 模式下增加一项可省略模板任务名的检查 @zzyyyl
- 文档杂项修改 (#6485) @Rbqwow
- Update 3.5-肉鸽辅助协议.md @Lancarus
- 基建换班-编组缓存 使用value_or替代empty检查 (#6404) @status102
- 更新qodana配置 (#6465) @hxdnshx
- gui.log 在启动时记录当前版本 @ABA2396
- 在Python脚本中添加活动关导航下载与加载的示例 (#3916) (#6451) @ZhaoZuohong
- 删除多余的空任务 @zzyyyl
- debug: 增加一项多余空任务的检查 @zzyyyl
- fix algorithm error warning @Constrat
- reordered objects, following zh-cn @Constrat
- removed duplicate operator @Constrat
- Alter Operators ^$ regex fix Yato alter, Noir alter, Terra Research ident. @Constrat
- 无配置字段时储存默认值 @ABA2396
- 全局选项设置减少嵌套，增加日志 @ABA2396
- i18n: Translations update from MAA Weblate @LiamSho
- Revert "chore: 兼容旧配置" @moomiji
- EN infrast workshop and i18n @Constrat
- tools: ignore templates @Constrat
- revert: 1095f9cf00162f30eae8666b4f63e87cad1d9857 Auto update has wrong time and event [skip ci] @Constrat
- 将其他语言的SSReopen说明修改为注释，目前仅支持国服/B服 (#6271) @status102
- I.S. missing EN translations. @Constrat
- 添加对账号切换的说明 (#6500) @A-JiuA
- 减少不必要的 try-catch @ABA2396
- A Flurry to the Flame event navigation @Constrat
- corrected a44dc12 time and event naming @Constrat
- 修正格式 @ABA2396
- 对CLI文档的侧边栏支持 (#6199) @SherkeyXD
- 尽可能稳定的打更多层数 -> 尽可能稳定地打更多层数 (#6200) @govizlora
- Untrastrated fix @wallsman
- 跟进蓝叠Hyper-V的连接指导 (#6083) (#6137) @SherkeyXD
- 取消连接时加载资源 @ABA2396
- 加点加载资源和连接模拟器的日志 @ABA2396
- i18n: Translations update from MAA Weblate (#6151) @weblate
- add log @AnnAngela


### For overseas

#### YostarKR

- update resources for YoStarKR @178619
- Update localization for YoStarKR @178619
- Update ocrReplaces for YoStarKR @178619

#### YostarEN

- EN SSReopen-XX adaptation @Constrat
- EN Guide Ahead navigation @Constrat
- 修复 EN 任务 `BattleQuickFormationFilter-Cost` @zzyyyl
- 修复 EN 生息演算任务 `Reclamation@ManufactureStatus` roi 越界的问题 @zzyyyl
- Gadget long name reduction for EN @Constrat
- docs: YostarEN recommended resolution (#6303) @Constrat
- new EN Roguelike@ChooseOperConfirm.png @Constrat
- YostarEN Reclamation Algorithm implementation (#6267) @ABA2396
- updated templates for EN (#6094) @Constrat

#### txwy

- 繁中服「敘拉古人」活動導航 @momomochi987
- 繁中文件大更新 (#6226) @momomochi987
- 對照陸服，整理與補充繁中服的 template 跟 tasks  (#6196) @momomochi987

#### YostarJP

- 添加日服生息演算翻译 | Reclamation Algorithm JP (#6340) @THSLP13
- (JP) Fix autoupdate change typo @wallsman
- （JP）紅炎遣らう落葉 Update @wallsman
- [JP] readme Update test / Japanese font readability (#6228) @wallsman

### For develops

- 支持woolang绑定 (#6142) @mrcino
- 把多镜像下载器应用于Python接口 (#6247) @HisAtri
- 🐞 fix(Java-HTTP): 修复Java-HTTP api的编译问题 (#6490) @gylove1994
