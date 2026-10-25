# ECHOES OF WAR

**A Dynamic Tactical Strategy · War Simulation · Real-Time Command Game**
**Built with Unreal Engine 5 + C++**

---

## Table of Contents
- [English](#english)
- [فارسی (Persian)](#فارسی)
- [中文 (Chinese)](#中文)

---
---

## English

### Overview
**ECHOES OF WAR** puts you in command of a military force inside a large,
persistent, simulation-driven war. There is no fixed sequence of missions:
frontlines, supply, morale, economy and diplomacy all emerge from a running
world simulation that keeps moving whether or not you're watching a
particular region. You play across three layers — **Strategic**
(policy, budget, research, front priorities), **Operational** (moving
brigades, planning multi-stage operations, routing supply) and
**Tactical** (direct command in an active engagement).

### Key Features
- **World Simulation Engine** — every region tracks population, economy,
  security, loyalty, infrastructure, morale and political stability, and
  these values genuinely drive gameplay.
- **Independent Faction AI** — each faction has its own doctrine, economy
  and army, and decides where to reinforce, attack, retreat or negotiate
  based only on what it can actually observe (no cheating, no hidden
  omniscience).
- **Persistent Units & Commanders** — experience, fatigue, morale,
  equipment condition, training, supply status and combat history all
  persist across battles; losing a veteran commander or unit has lasting
  consequences.
- **Deep Logistics & Supply Chain** — resources flow Factory → Warehouse →
  Transport Hub → Depot → Frontline Unit, throttled by distance, road
  damage, enemy threat and weather.
- **Fog of War & Multi-Source Intelligence** — Recon, Drones, Radar,
  Observation Posts, Satellites, Signals and HUMINT each report with their
  own confidence level; reports can disagree.
- **Command Hierarchy & Order Execution** — orders can be delayed,
  degraded or refused based on communications, morale, suppression,
  fatigue and officer quality.
- **Research, Military Industry & Diplomacy** — a full technology tree,
  factories constrained by real resource/power/labor/security inputs, and
  a reputation-driven diplomacy system (alliances, ceasefires, trade,
  intel sharing, military aid).
- **Dynamic Events, War News & War Chronicle** — every event is generated
  from actual world state, never a scripted, disconnected occurrence.
- **Battle Replay & After Action Review** — scrub back through a battle
  with multiple cameras and heatmaps; multi-metric operation scoring
  (objectives, resource efficiency, unit preservation, strategic
  stability) rather than a simple kill count.
- **Scenario Editor & Modding** — maps, factions, units, technology,
  doctrines and events are all data-driven (JSON + Data Assets) and can be
  authored without touching C++.
- **Multiplayer-Ready Architecture** — the simulation core is fully
  independent of networking; an optional server-authoritative layer
  (Co-op Command / Competitive Faction Warfare) sits on top of it.

### UI Themes & Languages
Six built-in UI themes: **Windows 11** (default, acrylic + rounded
corners), **Light**, **Dark**, **High Contrast**, **Blue Command** and
**Red Alert**. Three fully supported interface languages — **English**,
**Persian** and **Chinese** — with correct text direction per language
(Persian renders right-to-left; English and Chinese render left-to-right)
and font fallback so every script displays correctly. The simulation
clock (real seconds per simulated day, resupply cycle length, and the
"next update in…" countdown shown in Settings) is fully configurable by
the player — nothing about pacing is hard-coded.

### Technology Stack
| Layer | Technology |
|---|---|
| Engine | Unreal Engine 5.4+ |
| Core simulation & systems | C++ |
| Designer workflow / UI wiring | Blueprint (UMG) |
| Data-driven content | JSON, Unreal Data Assets |
| Save data | Unreal `USaveGame` + JSON subsystem blobs + MD5 checksum |
| Networking (optional) | Server-authoritative replication (`AGameStateBase`) |
| Build automation | PowerShell scripts, Unreal `UnrealBuildTool` / `RunUAT` |

### Project Structure
```
EchoesOfWar.uproject
Source/
  EchoesOfWar/          Main game module (GameMode, GameInstance, PlayerController)
  EchoesOfWarCore/       Shared IDs, enums, structs
  Simulation/            World/region/weather/day-night/frontline/events/civilians
  AI/                    Faction commander AI, tactical AI, doctrine, AI debugger
  Units/                 Persistent units, equipment, command hierarchy, orders,
                         comms, morale, fatigue, medical, prisoners
  Combat/                Combat resolution, fog of war, intelligence
  Logistics/             Supply chain, convoys, strategic pathfinding
  Economy/               Resource economy, military industry
  Politics/              Diplomacy
  Research/              Technology tree
  World/                 Static map/settlement/terrain data
  Save/                  Save/load, versioning, integrity checksum
  Networking/            Optional multiplayer shell
  UI/                    Themes, localization, advisors, news, chronicle,
                         achievements, replay, after-action review
  Tools/                 Scenario editor utility, content validation, mod
                         loader, debug console, performance profiler,
                         automated scenario test runner
Content/
  Data/                  Factions, doctrines, unit templates, technology,
                         scenarios (JSON)
  Localization/          en / fa / zh string tables
  UI/Themes/             Theme palette JSON mirrors
Tests/                   Automation test suite
Config/                  Engine/Game/Input .ini
Scripts/                 setup-windows.ps1, build-development.ps1,
                         build-shipping.ps1, run-tests.ps1, package.ps1
Docs/                    GDD, TDD, Architecture, Modding, Scenario
                         Authoring, AI, Save System, Localization, Build,
                         Troubleshooting guides
```

### Installation (Windows)
1. **Install Git** — https://git-scm.com/download/win
2. **Install Visual Studio 2022** — https://visualstudio.microsoft.com/vs/
   and enable the **"Game development with C++"** workload plus the
   **Windows 10/11 SDK**.
3. **Install Unreal Engine 5.4+** via the Epic Games Launcher.
4. **Extract this project's zip file** to a folder of your choice.
5. Open PowerShell in that folder and run:
   ```powershell
   .\Scripts\setup-windows.ps1
   ```
   to confirm every prerequisite is detected.
6. Right-click `EchoesOfWar.uproject` → **Generate Visual Studio project
   files**, then open the `.uproject` (or the generated `.sln`).
7. Build:
   ```powershell
   .\Scripts\build-development.ps1
   ```
8. Run tests:
   ```powershell
   .\Scripts\run-tests.ps1
   ```
9. Package a Shipping build:
   ```powershell
   .\Scripts\build-shipping.ps1
   ```
Full details and troubleshooting: `INSTALLATION.md`, `Docs/BUILD_GUIDE.md`,
`Docs/TROUBLESHOOTING.md`.

### Project Status
This repository is a large, working **C++/Unreal Engine 5 architectural
foundation**: every system described above is implemented with real logic
(simulation math, AI decision rules, supply-chain flow, save-integrity
checks, and more), organized into clean, modular, independently testable
code — not placeholders. It is **not** a finished, art-complete, balanced,
shipped title: reaching that point from here still requires UE5 content
(maps, meshes, VFX, audio), extensive balancing and QA, and additional
scenarios authored through the Scenario Editor. Every system here is
built to be extended.

### License
Add your preferred license file (e.g. `LICENSE.md`) before distributing
this project publicly.

---
---

## فارسی

### معرفی
**پژواک‌های جنگ (ECHOES OF WAR)** شما را در نقش فرمانده یک نیروی نظامی
در دل یک جنگ بزرگ، پایدار و مبتنی بر شبیه‌سازی قرار می‌دهد. هیچ توالی
ثابتی از مأموریت‌ها وجود ندارد: خطوط مقدم، تدارکات، روحیه، اقتصاد و
دیپلماسی همگی از یک شبیه‌سازی زنده جهان بیرون می‌آیند که حتی وقتی شما به
یک منطقه خاص نگاه نمی‌کنید نیز ادامه می‌یابد. بازی در سه سطح انجام
می‌شود: **راهبردی** (سیاست، بودجه، تحقیقات، اولویت جبهه‌ها)،
**عملیاتی** (جابه‌جایی تیپ‌ها، برنامه‌ریزی عملیات چندمرحله‌ای، مسیر
تدارکات) و **تاکتیکی** (فرماندهی مستقیم در یک نبرد فعال).

### ویژگی‌های کلیدی
- **موتور شبیه‌سازی جهان** — هر منطقه جمعیت، اقتصاد، امنیت، وفاداری،
  زیرساخت، روحیه و ثبات سیاسی خود را دارد و این مقادیر واقعاً بر بازی
  اثر می‌گذارند.
- **هوش مصنوعی مستقل برای هر جناح** — هر جناح دکترین، اقتصاد و ارتش خاص
  خود را دارد و تصمیم‌های خود را فقط بر اساس آنچه واقعاً می‌بیند
  می‌گیرد؛ هیچ تقلب یا دانش پنهانی در کار نیست.
- **یگان‌ها و فرماندهان پایدار** — تجربه، خستگی، روحیه، وضعیت تجهیزات،
  آموزش، وضعیت تدارکات و تاریخچه نبرد همگی بین نبردها حفظ می‌شوند؛ از
  دست دادن یک فرمانده یا یگان باتجربه پیامدهای واقعی دارد.
- **لجستیک و زنجیره تأمین عمیق** — منابع از کارخانه به انبار، مرکز حمل‌
  و‌نقل، دپو و سپس یگان خط مقدم جریان می‌یابند و فاصله، آسیب جاده، تهدید
  دشمن و آب‌وهوا آن را محدود می‌کنند.
- **مه جنگ و اطلاعات چندمنبعی** — شناسایی، پهپاد، رادار، پاسگاه دیده‌بانی،
  ماهواره، سیگنال و منابع انسانی هرکدام با سطح اطمینان خود گزارش می‌دهند
  و ممکن است با هم اختلاف داشته باشند.
- **زنجیره فرماندهی و اجرای دستورات** — دستورات می‌توانند بر اساس
  ارتباطات، روحیه، سرکوب، خستگی و کیفیت افسران با تأخیر، ضعف یا حتی عدم
  اجرا مواجه شوند.
- **تحقیقات، صنعت نظامی و دیپلماسی** — یک درخت فناوری کامل، کارخانه‌هایی
  که به منابع، برق، نیروی کار و امنیت واقعی وابسته‌اند و سیستم دیپلماسی
  مبتنی بر اعتبار (اتحاد، آتش‌بس، تجارت، اشتراک اطلاعات، کمک نظامی).
- **رویدادهای پویا، اخبار جنگ و وقایع‌نامه جنگ** — هر رویداد از وضعیت
  واقعی جهان تولید می‌شود، نه یک اتفاق از پیش نوشته‌شده و بی‌ربط.
- **بازپخش نبرد و گزارش پس از عملیات** — مرور نبرد با چند دوربین و
  نقشه‌های حرارتی؛ امتیازدهی چندمعیاره عملیات (تکمیل اهداف، بهره‌وری
  منابع، حفظ نیرو، ثبات راهبردی) به‌جای شمارش ساده کشته‌ها.
- **ویرایشگر سناریو و مادینگ** — نقشه‌ها، جناح‌ها، یگان‌ها، فناوری،
  دکترین‌ها و رویدادها همگی داده‌محور (JSON و Data Asset) هستند و بدون
  نیاز به C++ قابل ساخت‌اند.
- **معماری آماده چندنفره** — هسته شبیه‌سازی کاملاً مستقل از شبکه است؛
  یک لایه اختیاری سرور-محور (فرماندهی مشترک یا جنگ رقابتی جناح‌ها) روی
  آن قرار می‌گیرد.

### پوسته‌ها و زبان‌های رابط کاربری
شش پوسته آماده رابط کاربری: **ویندوز ۱۱** (پیش‌فرض، با افکت اکریلیک و
گوشه‌های گرد)، **روشن**، **تیره**، **کنتراست بالا**، **فرماندهی آبی** و
**هشدار قرمز**. سه زبان کامل رابط کاربری — **انگلیسی**، **فارسی** و
**چینی** — با جهت متن صحیح برای هر زبان (فارسی راست‌به‌چپ و انگلیسی/چینی
چپ‌به‌راست نمایش داده می‌شوند) و فونت جایگزین برای نمایش صحیح هر رسم‌خط.
ساعت شبیه‌سازی (ثانیه واقعی به ازای هر روز شبیه‌سازی، طول چرخه تأمین
مجدد، و شمارش معکوس «به‌روزرسانی بعدی تا...» در تنظیمات) کاملاً توسط
بازیکن قابل تنظیم است — هیچ‌چیز درباره سرعت بازی ثابت و کدگذاری‌شده
نیست.

### نصب (ویندوز)
۱. **نصب Git** — از آدرس https://git-scm.com/download/win
۲. **نصب Visual Studio 2022** — از آدرس
   https://visualstudio.microsoft.com/vs/ و فعال‌سازی بار کاری
   **"Game development with C++"** به‌همراه **Windows 10/11 SDK**.
۳. **نصب Unreal Engine 5.4 یا بالاتر** از طریق Epic Games Launcher.
۴. **استخراج فایل زیپ این پروژه** در پوشه‌ای دلخواه.
۵. باز کردن PowerShell در آن پوشه و اجرای:
   ```powershell
   .\Scripts\setup-windows.ps1
   ```
   برای بررسی نصب صحیح همه پیش‌نیازها.
۶. کلیک راست روی `EchoesOfWar.uproject` و انتخاب **Generate Visual
   Studio project files**، سپس باز کردن فایل `.uproject` (یا `.sln`
   تولیدشده).
۷. کامپایل:
   ```powershell
   .\Scripts\build-development.ps1
   ```
۸. اجرای تست‌ها:
   ```powershell
   .\Scripts\run-tests.ps1
   ```
۹. ساخت نسخه نهایی (Shipping):
   ```powershell
   .\Scripts\build-shipping.ps1
   ```
جزئیات کامل و رفع اشکال: `INSTALLATION.md`، `Docs/BUILD_GUIDE.md` و
`Docs/TROUBLESHOOTING.md`.

### وضعیت پروژه
این مخزن یک **بنیاد معماری بزرگ و کاربردیِ C++/Unreal Engine 5** است: هر
سیستمی که در بالا توضیح داده شد با منطق واقعی (محاسبات شبیه‌سازی، قواعد
تصمیم‌گیری هوش مصنوعی، جریان زنجیره تأمین، بررسی صحت ذخیره‌سازی و موارد
دیگر) پیاده‌سازی شده و در کدی تمیز، ماژولار و قابل‌آزمایش مستقل سازمان‌
دهی شده است — نه صرفاً جای‌گیرنده‌های خالی. این پروژه **یک بازی نهایی،
کامل از نظر گرافیکی، متعادل‌شده و منتشرشده نیست**: رسیدن به آن نقطه از
اینجا همچنان به محتوای Unreal Engine (نقشه، مدل، جلوه‌های ویژه، صدا)،
تعادل‌بخشی و آزمایش گسترده و سناریوهای بیشترِ ساخته‌شده با ویرایشگر
سناریو نیاز دارد. هر سیستم اینجا برای توسعه بیشتر طراحی شده است.

---
---

## 中文

### 概述
**《战争回声》(ECHOES OF WAR)** 让你在一个庞大、持久、由模拟驱动的战争
中指挥一支军事力量。游戏没有固定的任务序列：战线、补给、士气、经济和
外交都从一个持续运行的世界模拟中自然产生，即使你没有关注某个特定区域，
它也会持续运转。游戏分为三个层级：**战略层**（政策、预算、科研、战线
优先级）、**战役层**（调动旅/营级部队、规划多阶段行动、规划补给路线）
和**战术层**（在实际交战中直接指挥部队）。

### 核心特性
- **世界模拟引擎** — 每个地区都追踪人口、经济、安全、忠诚度、基础设施、
  士气和政治稳定性，这些数值真实地驱动着游戏进程。
- **各自独立的阵营人工智能** — 每个阵营拥有自己的作战条令、经济和军队，
  仅根据自己能够实际观察到的信息做出增援、进攻、撤退或谈判的决定——
  绝无作弊，绝无隐藏的全知视角。
- **持久化的部队与指挥官** — 经验、疲劳、士气、装备状况、训练水平、补给
  状态和战斗历史都会在战斗之间保留；失去一位老练的指挥官或部队将带来
  真实且持久的后果。
- **深度后勤与供应链** — 资源沿工厂 → 仓库 → 运输枢纽 → 补给站 → 前线
  部队流动，其效率受距离、道路损毁、敌方威胁和天气的制约。
- **战争迷雾与多来源情报** — 侦察兵、无人机、雷达、观察哨、卫星、信号
  情报和人力情报各自以不同的置信度上报，报告之间可能存在分歧。
- **指挥体系与命令执行** — 命令可能因通讯状况、士气、压制、疲劳和军官
  素质而延迟、打折扣，甚至被拒绝执行。
- **科研、军事工业与外交** — 完整的科技树，产能受真实资源、电力、劳动力
  和安全状况制约的工厂，以及基于声誉的外交系统（结盟、停火、贸易、情报
  共享、军事援助）。
- **动态事件、战争新闻与战争编年史** — 每一个事件都由真实的世界状态生成，
  绝非脱离实际、预先写好的桥段。
- **战斗回放与战后讲评** — 通过多机位和热力图回顾战斗；采用多维度的
  行动评分（目标完成度、资源效率、部队保存率、战略稳定性），而非单纯的
  击杀数统计。
- **场景编辑器与模组支持** — 地图、阵营、部队、科技、条令和事件均为
  数据驱动（JSON 与 Data Asset），无需修改 C++ 即可创建。
- **面向多人游戏的架构** — 模拟核心与网络功能完全解耦；一个可选的
  服务器权威层（合作指挥或阵营竞技战争）叠加在其之上。

### 界面主题与语言
内置六种界面主题：**Windows 11**（默认，亚克力效果+圆角）、**浅色**、
**深色**、**高对比度**、**蓝色指挥**和**红色警戒**。完整支持三种界面
语言——**英语**、**波斯语**和**中文**——并为每种语言正确处理文字方向
（波斯语从右到左显示，英语与中文从左到右显示），并配备字体回退方案以
确保每种文字都能正确渲染。模拟时钟（每个模拟日对应的真实秒数、补给
周期长度，以及设置界面中显示的"距离下次更新还有…"倒计时）完全可由玩家
自行配置——节奏方面没有任何硬编码。

### Windows 安装步骤
1. **安装 Git** — 访问 https://git-scm.com/download/win
2. **安装 Visual Studio 2022** — 访问
   https://visualstudio.microsoft.com/vs/ ，并勾选
   **"使用 C++ 的游戏开发"** 工作负载以及 **Windows 10/11 SDK**。
3. 通过 Epic Games Launcher **安装 Unreal Engine 5.4 或更高版本**。
4. **解压本项目的 zip 压缩包**到任意文件夹。
5. 在该文件夹中打开 PowerShell 并运行：
   ```powershell
   .\Scripts\setup-windows.ps1
   ```
   以确认所有先决条件均已就绪。
6. 右键点击 `EchoesOfWar.uproject` → 选择 **Generate Visual Studio
   project files**，然后打开该 `.uproject` 文件（或生成的 `.sln`）。
7. 编译：
   ```powershell
   .\Scripts\build-development.ps1
   ```
8. 运行测试：
   ```powershell
   .\Scripts\run-tests.ps1
   ```
9. 打包 Shipping 版本：
   ```powershell
   .\Scripts\build-shipping.ps1
   ```
完整细节与故障排除请参见 `INSTALLATION.md`、`Docs/BUILD_GUIDE.md` 与
`Docs/TROUBLESHOOTING.md`。

### 项目现状
本仓库是一个规模庞大且可运行的 **C++ / Unreal Engine 5 架构基础**：
上述每一个系统都以真实逻辑实现（模拟计算、AI 决策规则、供应链流转、
存档完整性校验等等），并组织为清晰、模块化、可独立测试的代码——而非
占位符。它**并非**一款美术完整、经过平衡调校、已发行的最终游戏：从
现有基础走到那一步，仍需要 Unreal Engine 美术资源（地图、模型、特效、
音频）、大量的平衡性调整与测试，以及通过场景编辑器创作更多场景。这里
的每一个系统都是为进一步扩展而设计的。
