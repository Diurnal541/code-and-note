// 定义Base58的字母表
var alphabet = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz';

// 输入的Base58编码字符串
var input = '5NEPwcfpCrstwRvMJnYLcAoEVcgZahBUZPPJDTAUnXcGXJxQKYGUteFoLZbxNCaMJmVhZZCkbJCVcBYBjaQJdUsLpxpEstUxPTrfHGmEFfzKKSXiHcXHwTbSrZXyLbwFviTCtYcFXTycBEZdzWitUDeWbrcXQLsPWzyuhgFvqNZmEfWrwoAxQcnSnyPVVfVdmFrturgWwWEiRkyqNqyHwhwwPyWdeJLcVxfUzbMUYUDhNbjRjbHPixWokxqFSUDBNQMGMHbGmfuLbyBowKBgScqmqrFcdagMxYmKuXjRBMKXKRIKVwGNHqKtSMejHKvcEMtLVUuDJTbBtkVhiPHvpkPbrtmBEonpGmwizAprTtGpqFnGAqiSSnFvunDuVCEmStaiRkkbBmyWdFrhJcPRfzCTcqZYxdXysNpQCeAhrrBvibePhtyGLSdthKtQTbovHpUgkcEatapvLswwDUXbikBoHiqJDCJbjWUErgvTEmvuGAGEXNJSgSeTJagnbgbZdooXVXVybyGtoLNptdqsqrFnqNBFNipREDTtHYkBskcSwtKfVGWd';

// 创建一个ByteArray来存储解码后的结果
var byteArray = [];

// 遍历输入的Base58编码字符串
for (var i = 0; i < input.length; i++) {
    var value = alphabet.indexOf(input[i]);
    for (var j = 0; j < byteArray.length; j++) {
        value += byteArray[j] * 58;
        byteArray[j] = value & 0xff;
        value >>= 8;
    }
    while (value > 0) {
        byteArray.push(value & 0xff);
        value >>= 8;
    }
}

// 反转ByteArray以获得正确的顺序
byteArray.reverse();

// 输出解码后的ByteArray
console.log(byteArray);
