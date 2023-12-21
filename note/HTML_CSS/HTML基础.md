# HTML基础

## HTML标题

HTML的标题（Headig）是通过\<h1> - \<h6>等标签进行定义的

```html
<h1>This is a heading</h1>
<h2>This is a heading</h2>
<h3>This is a heading</h3>
```

\<hr />标签在HTML页面中创建水平线
hr元素可用于分隔内容

```html
<p>This is a paragraph</p>
<hr />
<p>This is a paragraph</p>
<hr />
<p>This is a paragraph</p>
```



## HTML段落

HTML段落是通过\<p>标签进行定义的

```html
<p>This is a paragraph.</p>
<p>This is another paragraph.</p>
```

\<br />元素可以进行换行

```html
<p>This is<br />a para<br />graph with line breaks</p>
```



## HTML链接

HTML链接是通过\<a>标签进行定义的

```html
<a href="http://www.w3school.com.cn">This is a link</a>
```

## HTML图像

HTML图像是通过\<img>标签进行定义的

```html
<img src="w3school.jpg" width="104" height="142" />
```

## HTML元素

HTML元素指的是从开始标签（start tag）到结束标签（end tag）的所有代码

| 开始标签                 | 元素内容            | 结束标签 |
| ------------------------ | ------------------- | -------- |
| \<p>                     | This is a paragraph |          |
| \<a href="default.html"> | This is a link      |          |
| \<br />                  |                     |          |

开始标签常被称为开放标签（opening tag），结束标签常被称为闭合标签（closing tag）

HTML元素语法：

* HTML元素以开始标签起始
* HTML元素以结束标签终止
* 元素的内容是开始标签与结束标签之间的内容
* 某些HTML元素具有空内容（empty content）
* 空元素在开始标签中进行关闭（以开始标签的结束而结束）
* 大多数HTML元素可拥有属性

### \<p>元素：

```html
<p>This is my first paragraph</p>
```

### \<body>元素：

```html
<body>
    <p>This is my first paragraph</p>
</body>
```

\<body>元素定义了HTML文档的主体

### \<html>元素

```html
<html>
    <body>
        <p>This is my first paragraph</p>
    </body>
</html>
```

\<html>元素定义了整个HTML文档

### 空的HTML元素

没有内容的HTML元素被称为空元素。空元素是在开始标签中被关闭的
\<br>就是没有关闭标签的空元素，该元素定义换行
在开始标签中添加斜杆，比如\<br/>是关闭空元素的正确方法

## HTML属性

HTML链接由\<a>标签定义，链接的地址在href属性中指定

```html
<a href="http://www.w3school.com.cn">This is a link</a>
```

```html
<h1 align="center"/> 标题居中对齐
<body bgcolor="yellow"/> 背景为黄色
<table border="1"/> 设置边框
```

适用于大多数HTML元素的属性：

| 属性  | 值               | 描述               |
| ----- | ---------------- | ------------------ |
| class | classname        | 规定元素的类名     |
| id    | id               | 规定元素的唯一id   |
| style | style_definition | 规定元素的行内样式 |
| title | text             | 规定元素的额外信息 |

## HTML注释

```html
<!-- This is a comment -->
```

开始括号之后需要紧跟一个叹号，结束括号之前不需要

## HTML样式

在HTML4中，有若干标签和属性是被废弃的。被废弃的意思是在未来版本的HTML和XHTML中将不支持这些标签和属性。

| 标签                 | 描述           |
| -------------------- | -------------- |
| \<center>            | 定义居中的内容 |
| \<font>和\<basefont> | 定义HTML字体   |
| \<s>和\<strike>      | 定义删除线文本 |
| \<u>                 | 定义下划线文本 |

| 属性    | 描述               |
| ------- | ------------------ |
| align   | 定义文本的对齐方式 |
| bgcolor | 定义背景颜色       |
| color   | 定义文本颜色       |

**对于这些标签和属性：请使用样式替代！**

backgound-color属性为元素定义了背景颜色：

```html
<html>

<body style="background-color:yellow">
<h2 style="background-color:red">This is a heading</h2>
<p style="background-color:green">This is a paragraph.</p>
</body>

</html>
```

