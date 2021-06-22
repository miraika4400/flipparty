新たに.cppや.hをフォルダに追加した場合は以下の設定が必要です。

プロジェクト→プロパティ→C/C++→全般
の中にある追加インクルードディレクトリにてソースのあるフォルダを指定してください。
なお指定する際には構成を”すべての構成”に指定してから作業を行ってください。（Relese・Debug両ビルドに対応させるため）

ディレクトリの指定方法ですが今回はソリューションファイルを開始位置として登録します。
以下のディレクトリ構成において”debug_font.h”を使用したい場合、そのファイルが格納されているフォルダを指定しください
今回はdebug_fontフォルダを指定します



flipparty
┃
┣━━assets
┣━━.gitignore
┗━━project
	┃
	flipparty
	┃
	┣━━flipparty.sln
	┃
	┗━━flipparty
		┃
		┣━━flipparty.vcxproj
		┣━━flipparty.vcxproj.filters
		┣━━flipparty.vcxproj.user
		┣━━data
		┗━━source
			┃
			┣━━debug_font
			┃	┃
			┃	┣━━debug_font.cpp
			┃	┗━━debug_font.h
			┃
			┣━━game
			┃	┃
			┃	┣━━game.cpp
				┗━━game.h


指定する際のパスの記載方法は

$(SolutionDir)/flipparty/source/debug_font

と記載してください

$(SolutionDir)/から始めるとソリューションファイルがあるところからフォルダの位置を探します。
$(ProjectDir)/から始めるとプロジェクトファイルがあるところからフォルダの位置を探します。