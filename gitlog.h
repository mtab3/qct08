#ifndef GITLOG_H
#define GITLOG_H


#define BRANCH_NAME ( "ext" )
#define GITLOGS ""\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Wed Oct 14 13:38:02 2015 +0900\n"\
                "    ・プログラムには変更なし\n"\"    ・光がある状態で動作チェックを行った\n"\"    　15,000点、30回スキャンを行った結果、後半に 3回データ転送ミスがあった。\n"\"      （ct08 <--> qct08 間の通信で正しいデータ点数よりも少ないデータしか受けられなかった）\n"\"      しかし、その結果は次の周回のデータには影響を与えなかった。\n"\"      (読み残しのデータが、次の回の頭に読まれて、スペクトルがシフトするというような現象は起こらなかった)\n"\"      今後、期待している点数よりも少ない数しかデータを受けられなかった時の対策をもう少し練る。\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Oct 13 20:11:09 2015 +0900\n"\
                "    Merge remote-tracking branch 'origin/ext-chs' into ext-chs\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Oct 13 20:00:24 2015 +0900\n"\
                "    ext-chs :\n"\"    a) 主に、カウンタで蛍光 quick を行うため、複数チャンネルを束ねた仮想チャンネルを作り\n"\"       束ねられたチャンネルの合計値を取得できるようにした。\n"\"    b) より古い変更だが、動作確認されていない機能として 9999 点を超えるカウントに\n"\"       対応できているはず。\n"\"    \n"\"    光がない状態で下記の点をチェック\n"\"    \n"\"    1) ext-chs の機能(仮想チャンネル)を使わず、かつ データ点数 < 10,000\n"\"    2) ext-chs の機能を使い、かつ データ点数 < 10,000\n"\"    3) ext-chs の機能を使わず、かつ データ点数 >= 10,000\n"\"    4) ext-chs の機能を使い、かつ データ点数 >= 10,000\n"\"    \n"\"    上記、4条件で全て正常。\n"\"    ここで正常としたのは、Function Generator から入れた 5MHz の信号を\n"\"    仮想の測定信号として、30〜50回のクイックスキャンを行い、\n"\"    適切な数値(5,000,000 cps (束ねたチャンネルではこれの整数倍))が\n"\"    適切な点数測定されたことを意味する。\n"\"    従って、おおよそ正常動作しているものと判断できる。\n"\"    \n"\"    但し、\n"\"    上記のチェックでは、全データ点でデータの数値がほぼ同じなので(5,000,000cps)、\n"\"    データがズレても、そのことはわからない。\n"\"    従って、光があるときにこの点をチェック（スペクトルがエネルギーに対してシフトしない）して\n"\"    最終確認とし、stable (or master) にマージする予定\n"\
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
                "Author      : Masao TABUCHI <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Wed Sep 16 16:20:09 2015 +0900\n"\
                "    modify qct08.cfg\n"\
		"\n"\
                "Author      : Masao TABUCHI <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Sep 15 15:59:26 2015 +0900\n"\
                "    仮想の複合チャンネルサポート\n"\"    これまでも(光がある状態ではチェックしていないが) GetValue では\n"\"    複合チャンネルからのでデータ読み出しができていたはず。\n"\"    今回は、qGetData でも複合チャンネルをサポートしたつもり。\n"\"    いずれにしても、光がある状態では未確認。\n"\
		"\n"\
                "Author      : Masao TABUCHI <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Sep 15 13:49:49 2015 +0900\n"\
                "    merged with master\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Mon Sep 14 19:05:06 2015 +0900\n"\
                "    1) 測定点数が変動する問題に対して、stable ブランチに施して有効だった\n"\"    　qInitialize 内で タイマーをリセットする対策を施した。\n"\"    2) この対策を施した時点で XafsM2 と組み合わせて連続 quick 測定試験を行う(光有り)。\n"\"    　[Cu-K, 標準 XANES (4665点, 120秒),\n"\"    　　　I0 : Qct100MHz, I1 : Qct100MHz, I2 : 未使用]\n"\"    　a) 25回スキャンした時点で、測定点数は一度も変動せず。\n"\"    　b) 元の master ブランチでは 17回 スキャンした時点で発生していたデータが異常になる\n"\"      　　症状が消えた。\n"\"      　　(おそらく、測定時間で割り算して、時間あたりのカント数に直すところで\n"\"      　　　何かトラブルがあった?)\n"\"      c) 測定点数を 9999点以上にする機能も入っているが、これはまだ未確認\n"\
		"\n"\
                ""
#endif
