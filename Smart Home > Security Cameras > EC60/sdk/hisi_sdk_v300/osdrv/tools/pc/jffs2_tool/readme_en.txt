1.The open-source tool mtd-utils2.0.2 does not provide the source code package. Download the mtd-utils-2.0.2.tar.bz2 source code package to the current directory before using it.
	Download website: https://src.fedoraproject.org/repo/pkgs/mtd-utils/mtd-utils-2.0.2.tar.bz2/
The mtd-utils2.0.2 depends on the LZO tool. Download the lzo-2.09.tar.gz source code package to the current directory before using it.
	Download website: http://www.oberhumer.com/opensource/lzo/download/ 

2.mtd-utils2.0.2 depends on the following libraries, taking ubuntu as an example. For the installation method, please refer to the following command:
    sudo apt-get install zlib1g-dev liblzo2-dev uuid-dev pkg-config

3.Since mtd-utils2.0.2 checks whether each library is installed normally through the pkg-config tool, please set the pkg-config tool search path as follows:
    export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/lib/x86_64-linux-gnu/pkgconfig"

4. mtd-utils2.0.2 depends on automake1.15.1 version, please refer to the following way to install automake1.15.1 version:
    (1). Delete the original automake version
        sudo apt-get autoremove automake
    (2). Download automake1.15.1 version
	    1). Windows system uses a browser to access the automake project url and download the corresponding source package:
            https://lists.gnu.org/archive/html/info-gnu/2017-06/msg00007.html
        2). Linux system can be downloaded using the following command:
            wget ftp://ftp.gnu.org/gnu/automake/automake-1.15.1.tar.gz
    (3). Compile and install automake1.15.1:
	    tar zxvf automake-1.15.1.tar.gz
	    cd automake-1.15.1/
	    ./configure
	    make
	    make install

5. Compile mtd-utils2.0.2
