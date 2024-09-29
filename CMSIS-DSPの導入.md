# CMSIS-DSPの導入

## 手始め
まずは、STM32CubeIDEを入れておく

環境設定は済ませておく

プロジェクトを作成する過程でいろいろなダウンロードが行われるので、STM32CubeIDEで1回は実行まで行っていること

## 準備
"C:\Users\(名前)\STM32Cube\Repository"

Cドライブ(OSとかが保存されているところ)の中にある "users" といフォルダに自分の名前？？のフォルダがある

その中に "STM32Cube" フォルダがある

(もし、見つからない場合はSTM32CubeIDEで新しいプロジェクトを作るとダウンロードが行われる)


 "STM32Cube" → "Repository" を開く

### "Repository" の中に "STM32Cube_FW_G4_V1.6.0" が無い場合
(Vの後の数字はバージョンによるので同じでなくてもいい)

https://www.st.com/ja/embedded-software/stm32cubeg4.html
から "STM32Cube MCU Package for STM32G4 series" をインストールし 
"C:\Users\(名前)\STM32Cube\Repository" の中に展開する

## 移動する

" ... \Repository\STM32Cube_FW_G4_V1.6.0\Drivers\CMSIS\DSP\Lib" 

"STM32Cube_FW_G4_V1.6.0" → "Drivers" → "CMSIS" → "DSP" → "Lib" を開く

"Lib" の中にある "ARM" フォルダから "arm_cortexM4lf_math.lib" , 
"GCC" フォルダから "libarm_cortexM4lf_math.a" をコピーする

"C:\Users\(名前)\STM32CubeIDE\workspace_1.16.1\(プロジェクト名)"

"STM32Cube" のファイルがあった場所と同じところに "STM32CubeIDE" がある

"STM32CubeIDE" の中にある "workspace_1.16.1" (数字はバージョンによるので使用しているバージョンのファイル)の中にある "(使用したいプロジェクトフォルダ)" に貼り付ける

" ... \Repository\STM32Cube_FW_G4_V1.6.0\Drivers\CMSIS\DSP\Include"

同様に "Include"を開き、"Include" の中にある全てをコピーし

"C:\Users\(名前)\STM32CubeIDE\workspace_1.16.1\(プロジェクト名)\Core\Inc"

"(使用したいプロジェクトフォルダ)" → "Core" → "Inc" を開き貼り付ける

## アプリの設定

STM32CubeIDEアプリケーションでCMSIS-DSPを使用したいプロジェクトを開く

上のタブにある "Project" → "Properties" → "C/C++Build" を開く → "Setting" → "ToolSettings" → "MCU/MPU G++ Linker" を開く → "Libraries"

"Libraries (-l)" の右にある + (add) を押して "arm_cortexM4lf_math" を入力する

"Library search path (-L)" の右にある + (add) → "Workspace..." から使用したいプロジェクトを選択する　"${workspace_loc:/${ProjName}}" となっていればよい　

使用したいファイルで

#define ARM_MATH_CM4

#include "arm_math.h"

#include "arm_const_structs.h"

をインクルードすると使用できる



[次のページ](01_環境構築.md)

[STM32-メニュー](index.md)
