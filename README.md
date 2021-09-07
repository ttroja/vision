# vision
computer vision practice

- 拉取代码
```bash
$ git clone git@github.com:ttroja/vision.git
$ cd vision
$ git submodule update --init --recursive
```

- 编译
```bash
$ mkdir build && cd build
$ cmake ..
$ make -j8
$ # 运行单元测试
$ ./test/unittest/unitest
```