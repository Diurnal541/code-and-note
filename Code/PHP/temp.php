<?php
for ($i=32;$i<127;$i++){
    if (!preg_match("/[a-zA-Z1-9!'@#%^&*:{}\-<\?>\"|`~\\\\]/",chr($i))){
        echo chr($i)." ";
    }
}