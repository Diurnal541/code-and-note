// ����Base58����ĸ��
var alphabet = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz';

// �����Base58�����ַ���
var input = '5NEPwcfpCrstwRvMJnYLcAoEVcgZahBUZPPJDTAUnXcGXJxQKYGUteFoLZbxNCaMJmVhZZCkbJCVcBYBjaQJdUsLpxpEstUxPTrfHGmEFfzKKSXiHcXHwTbSrZXyLbwFviTCtYcFXTycBEZdzWitUDeWbrcXQLsPWzyuhgFvqNZmEfWrwoAxQcnSnyPVVfVdmFrturgWwWEiRkyqNqyHwhwwPyWdeJLcVxfUzbMUYUDhNbjRjbHPixWokxqFSUDBNQMGMHbGmfuLbyBowKBgScqmqrFcdagMxYmKuXjRBMKXKRIKVwGNHqKtSMejHKvcEMtLVUuDJTbBtkVhiPHvpkPbrtmBEonpGmwizAprTtGpqFnGAqiSSnFvunDuVCEmStaiRkkbBmyWdFrhJcPRfzCTcqZYxdXysNpQCeAhrrBvibePhtyGLSdthKtQTbovHpUgkcEatapvLswwDUXbikBoHiqJDCJbjWUErgvTEmvuGAGEXNJSgSeTJagnbgbZdooXVXVybyGtoLNptdqsqrFnqNBFNipREDTtHYkBskcSwtKfVGWd';

// ����һ��ByteArray���洢�����Ľ��
var byteArray = [];

// ���������Base58�����ַ���
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

// ��תByteArray�Ի����ȷ��˳��
byteArray.reverse();

// ���������ByteArray
console.log(byteArray);
