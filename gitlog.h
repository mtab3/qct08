#ifndef GITLOG_H
#define GITLOG_H


#define BRANCH_NAME ( "master" )
#define GITLOGS ""\
                "Author      : Masao TABUCHI <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Fri Nov 13 11:18:19 2015 +0900\n"\
                "    Merge remote-tracking branch 'origin/ext-chs' into ext-chs\n"\
		"\n"\
                "Author      : Masao TABUCHI <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Fri Nov 13 11:16:33 2015 +0900\n"\
                "    stop multi changedIsBusy\n"\
		"\n"\
                "Author      : Masao Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Wed Oct 14 18:02:22 2015 +0900\n"\
                "    it works for the QXafs measurements with 15,000 points and 30 times repetition\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Wed Oct 14 15:44:13 2015 +0900\n"\
                "    modify ct08.cpp to wait for data longer\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Wed Oct 14 13:38:02 2015 +0900\n"\
                "    ・プログラムには変更なし\n"\
"    ・光がある状態で動作チェックを行った\n"\
"    　15,000点、30回スキャンを行った結果、後半に 3回データ転送ミスがあった。\n"\
"      （ct08 <--> qct08 間の通信で正しいデータ点数よりも少ないデータしか受けられなかった）\n"\
"      しかし、その結果は次の周回のデータには影響を与えなかった。\n"\
"      (読み残しのデータが、次の回の頭に読まれて、スペクトルがシフトするというような現象は起こらなかった)\n"\
"      今後、期待している点数よりも少ない数しかデータを受けられなかった時の対策をもう少し練る。\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Oct 13 20:11:09 2015 +0900\n"\
                "    Merge remote-tracking branch 'origin/ext-chs' into ext-chs\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Oct 13 20:00:24 2015 +0900\n"\
                "    ext-chs :\n"\
"    a) 主に、カウンタで蛍光 quick を行うため、複数チャンネルを束ねた仮想チャンネルを作り\n"\
"       束ねられたチャンネルの合計値を取得できるようにした。\n"\
"    b) より古い変更だが、動作確認されていない機能として 9999 点を超えるカウントに\n"\
"       対応できているはず。\n"\
"    \n"\
"    光がない状態で下記の点をチェック\n"\
"    \n"\
"    1) ext-chs の機能(仮想チャンネル)を使わず、かつ データ点数 < 10,000\n"\
"    2) ext-chs の機能を使い、かつ データ点数 < 10,000\n"\
"    3) ext-chs の機能を使わず、かつ データ点数 >= 10,000\n"\
"    4) ext-chs の機能を使い、かつ データ点数 >= 10,000\n"\
"    \n"\
"    上記、4条件で全て正常。\n"\
"    ここで正常としたのは、Function Generator から入れた 5MHz の信号を\n"\
"    仮想の測定信号として、30〜50回のクイックスキャンを行い、\n"\
"    適切な数値(5,000,000 cps (束ねたチャンネルではこれの整数倍))が\n"\
"    適切な点数測定されたことを意味する。\n"\
"    従って、おおよそ正常動作しているものと判断できる。\n"\
"    \n"\
"    但し、\n"\
"    上記のチェックでは、全データ点でデータの数値がほぼ同じなので(5,000,000cps)、\n"\
"    データがズレても、そのことはわからない。\n"\
"    従って、光があるときにこの点をチェック（スペクトルがエネルギーに対してシフトしない）して\n"\
"    最終確認とし、stable (or master) にマージする予定\n"\
		"\n"\
                "Author      : Masao Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Oct 13 19:48:32 2015 +0900\n"\
                "    checking\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Oct 13 18:07:04 2015 +0900\n"\
                "    modified ct08.cpp to return correct number of datas by QGetData\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Fri Oct 9 21:26:36 2015 +0900\n"\
                "    The ext-ch is checked with SR.  It works well to sum up 3-SDD chs\n"\
		"\n"\
                ""
#endif
