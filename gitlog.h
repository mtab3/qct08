#ifndef GITLOG_H
#define GITLOG_H


#define BRANCH_NAME ( "ext" )
#define GITLOGS ""\
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
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Mon Sep 14 17:24:12 2015 +0900\n"\
                "    merge the change in 'check-dat-num-change'\n"\
		"\n"\
                "Author      : Masao Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Aug 11 20:52:55 2015 +0900\n"\
                "    made sure with no SR\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Aug 11 20:32:04 2015 +0900\n"\
                "    working on extra channels, getValue is ready\n"\
		"\n"\
                "Author      : M. Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Tue Aug 11 20:11:20 2015 +0900\n"\
                "    working on extra chnnels, ReadConf was edited\n"\
		"\n"\
                "Author      : Masao Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Mon Aug 10 12:19:44 2015 +0900\n"\
                "    Fix a small and add Makefile to .gitignore\n"\
		"\n"\
                "Author      : Masao Tabuchi <m.tabuchi@nusr.nagoya-u.ac.jp>\n"\
                "Date        : Mon Aug 10 12:16:20 2015 +0900\n"\
                "    Merge branch 'master' of titan.nusr.nagoya-u.ac.jp:prog/Qt0/qct08\n"\
		"\n"\
                ""
#endif
