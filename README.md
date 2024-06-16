# NTNU CSIE Computer Programming II Final Project

## Introduction

作者：吳振榮、吳立宇、伍駿宇

## Features

## 實作了哪些功能

### 基本需求

- 至少支援場景、人物、物品三種實體（完成）
- 至少支援場景背景、人物頭像、人物立繪、物品圖標等圖片素材（完成）
- 支援對話選項與多支線劇情設定（完成）
- 能實現劇本檔中期望呈現之內容（完成）
- 支援場景背景與人物立繪之疊加顯示（完成）
- 玩家需要有角色設定、可以放物品的背包（完成）
- 不能出現壞掉的排版（完成）
- 支援角色個人心情數值（完成）
- 至少要有三個角色（完成）
- 至少要有三個場景（完成）
- 至少要有兩個物品（完成）
- 至少要有三個結局（完成）
- README 說明書文件（完成）

### 額外功能

- 最佳實踐 GitHub（完成）
- 場景動畫（完成）
- 心情變換（完成）
- 遊戲存檔（完成）
- 音效播放（完成）
- LLM（未實作）
- 進階 Script 使用 Lua（未實作）

### 預期得分

100 (不含發表)

## Installation and Running

## 我們的遊戲如何玩

1. 將我們的程式載入到您的電腦內，下 make 指令編譯後，`./engine` 即可開始運行。

2. 遊戲點開出現三個選項
    - 第一個：開始遊玩
    - 第二個：查看這個遊戲的遊戲目的
    - 第三個：若有存檔案，可按此鍵繼續遊玩

3. 進入遊戲後，可根據顯示的文字，由下面三個選項，決定你想要的劇情發展。另外，藍色案件為存檔鍵，紅色按鈕點進去為背包。

4. 紅色背包點進去後，左上方圖案顯示心情的圖案，右邊是心情值，下方是目前遊戲中擁有的物品。

5. 藍色存檔鍵點進去後，你可以選擇存檔下次繼續玩，或取消。

## 劇本格式介紹

### 範例

```toml
script="script name"
start=1 //to determine the head of the script

[item]
{1,"name","pic.bmp"}

[player]
stat.name="luck"
stat=5

[npc]
{1,"name","pic.bmp","status_name",5}
{2,"name","pic.bmp",NULL,0}
//the status name and value must be set to NULL and 0 if not used

[1]
title="name"
background="background.bmp" //optional, but must be defined in the beginning
text="this is a test."
option={2,3,4} //the next option
to={3:5, -1:7} // 有物品3的話 跳到劇本5
item={-1,1,-1} //optional, put -1 if no condition, put id if need this item to get this option
player.stat=5 //optional, set player’s status value
player.inventory.add=1 //optional, can be multiple(?)
npc.1.stat=3 //optional, set npc’s stat value

[2]
title="test"
text="this is the end of the test."
option={0,0,0} //put 0 if no further option
player.stat=10
```

### 劇本先分成 開頭 物品 玩家 NPC 劇情

#### 開頭

- `script="script name"` 中填寫劇本的名稱
- `start=1` 表示劇本開始的 key（通常為 1）（key 為劇本裡中括號內的數字）

#### 物品

- `[item]` 用中括表示以下開始是物品 
- 範例：`{1,"name","pic.bmp"}`
  - `1` 為物品的編號 隨著你需要的物品數 可以自行自然數排下去
  - `"name"`為該物品的名稱
  - `"pic.bmp"`為該物品的照片 須提供照片的完整路徑

#### 玩家

- 我們遊戲中主畫面 有支援玩家的數值（數值名稱自訂）
- 在 `[player]` 中設定
- 範例：
  - `stat.name="state name"`
  - `stat=5`
  - `state name` 為該數值的名稱
  - `state` 的數值為該數值的起始值 可自訂

#### NPC

- `[npc]` 中設定，在劇情中會跳出的人物
- 範例：
  - `{1,"name","pic.bmp","status_name",5}`
  - `{2,"name","pic.bmp",NULL,0}`
  - `1` 第一個數值為 NPC 隻編號 同於物品
  - `"name"`為該 NPC 之名稱
  - `"pic.bmp"`為該 NPC 之圖片 須提供照片的完整路徑
  - `"status_name",5` 同玩家數值 但 NPC 可以選擇不要此功能 則填入 `NULL,0` 即可

### 劇情

#### 主要分成兩種格式

1. `option` 格式：有三個劇情發展，讓玩家選擇
2. `to` 格式：玩家無法選擇，根據玩家身上的物品，決定劇情發展

#### `option` 格式範例

```toml
[3]
title="書生"
background="img/background.jpg" 
text="你是一個大官的兒子，從小父母就給你很好的栽培"  
option={5,6,7} 
player.stat=60 
mood = { "img/nomood.jpg" , 60 }
```

- `[3]` 裡面的數值很重要，我們稱之為 `key`，為引導劇本的關鍵
- 一個 `key` 裡面的內容，我們稱之為節點，劇本的運行就是靠著不斷尋找下一個節點，直到結束（後面介紹如何結束）
- `title` 為該選項的標題，也是上一個節點中，玩家能看到選擇劇情的提示（`to` 格式後的劇情不需要 `title`）
- `background` 為該節點背景的圖面 須提供完整路徑
- `text` 玩家若選擇此劇情，會顯示的句子
- `option` 裡面填寫的三個數字，代表會接下去可能劇情的 `key`
- `player.stat` 為該節點顯示於主畫面玩家的數值
- `mood` 為支援心情值，顯示於點開包包後的地方，需填入兩的數值，前者為圖面，需提供完整路徑，後者為該心情數值

#### `to` 格式範例

```toml
[20]
title="反擊"
to = { 2:21 , -1:22 }
```

- `title` 若上一個節點為 `option` 格式，則有 `title`，同上，為上一個節點中，玩家能看到選擇劇情的提示
- `to` 這個概念是，假設玩家有 a 物品，就跳到 b 劇情，沒有則跳到 c 劇情
  - 其中填入四個數字，第一個數字為要檢測的物品編號，第二個數字為有該物品，跳到劇情的 `key`，第三個數字固定為 -1，表示沒有該物品，第四個數字則是沒有該物品跳到的劇情
  - 以範例中為例子：`to = { 2:21 , -1:22 }`
    - 意思是：如果有編號 2 這個物品，跳到 key 為 21 的劇情，沒有則跳到 22

## 檔案的存放位置
        
我們的專案中，包含四個資料夾：

- `DataSave` : 存放遊戲進度的檔案，若玩家有在遊戲中存檔過則會自動生成，可以自行修改裡面的內容。
- `font_lib` : 存放所有遊戲內會用到的字體。
- `img` : 存放所有遊戲劇本會用到的照片，可自行修改。
- `music` : 存放遊戲中會用到的音效。


### Requirements

## 如何設計一個劇本套用於我們的引擎

1. 從 GitHub 下載我們的程式
2. 下載 SDL 以及 SDL_mixer 和 SDL_ttf
3. 照著上述的劇本格式，完成一個劇本，檔案名稱取 `script.toml`
4. 將劇本會使用到的照片存入 `img` 資料夾
5. 準備 `how_to_play.txt` 文字檔，用於玩家選案 how to play 時生成的文字

### Setup

## 使用到的第三方工具

- SDL - [license](https://www.libsdl.org/license.php)
- Lovepik - [https://lovepik.com/images](https://lovepik.com/images) (載圖片)

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

- [吳振榮] - [WuMax13@gmail.com]
- Project Link: [https://github.com/yourusername/sdl-game-project](https://github.com/yourusername/sdl-game-project)
