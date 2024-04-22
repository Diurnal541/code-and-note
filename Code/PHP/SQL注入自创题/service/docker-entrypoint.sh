#!/bin/bash

# Get the user
user=$(ls /home)

# Check the environment variables for the flag and assign to INSERT_FLAG
if [ "$DASFALG" ]; then
    INSERT_FLAG="$DASFLAG"
elif [ "$FLAG" ]; then
    INSERT_FLAG="$FLAG"
elif [ "$GZCTF_FLAG" ]; then
    INSERT_FLAG="$GZCTF_FLAG"
else
    INSERT_FLAG="flag{TEST_Dynamic_FLAG}"
fi

# ��FLAGд���ļ� ������Ҫ����
echo $INSERT_FLAG | tee /home/$user/flag /flag

# ��FLAGд�����ݿ�

if [[ -z $FLAG_COLUMN ]]; then
    FLAG_COLUMN="flag"
fi

if [[ -z $FLAG_TABLE ]]; then
    FLAG_TABLE="flag"
fi

mysql -u root -p123456 -e "USE ctftraining;
ALTER TABLE FLAG_TABLE CHANGE FLAG_COLUMN $FLAG_COLUMN CHAR(128) NOT NULL DEFAULT 'not_flag';
ALTER TABLE FLAG_TABLE RENAME $FLAG_TABLE
INSERT INTO $INSERT_FLAG VALUES('$INSERT_FLAG');"

exec "$@"