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

### target属性

使用target属性，你可以定义被链接的文档在何处显示。
下面这行会在新窗口打开文档：

```html
<a href="http://www.w3school.com.cn/" target="_blank">Visit W3School!</a>
```

|   属性    |                             描述                             |
| :-------: | :----------------------------------------------------------: |
|  _blank   |               在新窗口或者标签页中打开链接文档               |
|   _self   | 在与被点击的链接相同的框架中打开链接文档（这是默认值，通常不需要指定） |
|  _parent  |                    在父框架中打开链接文档                    |
|   _top    |                在窗口的整个主体中打开链接文档                |
| framename |                在指定的命名框架中打开链接文档                |

### name属性

name 属性规定锚（anchor）的名称。
您可以使用 name 属性创建 HTML 页面中的书签。
书签不会以任何特殊方式显示，它对读者是不可见的。
当使用命名锚（named anchors）时，我们可以创建直接跳至该命名锚（比如页面中某个小节）的链接，这样使用者就无需不停地滚动页面来寻找他们需要的信息了。

```html
<a name="label">锚</a>
<!--锚的名字可以是任何你喜欢的名字，可以使用id属性来替代name属性，命名锚同样有效-->
<!--首先，我们在HTML文档中对锚进行命名（创建一个书签）：-->
<a name="tips">基本的注意事项 - 有用的提示</a>
<!--然后，我们在同一个文档中创建指向该锚的链接：-->
<a href="#tips">有用的提示</a>
<!--您也可以在其他页面中创建指向该锚的链接：-->
<a href="http://www.w3school.com.cn/html/html_links.asp#tips">有用的提示</a>
```

**命名锚通常用于在大型文档开始位置上创建目录。可以为每个章节赋予一个命名锚，然后把链接到这些锚的链接放到文档的上部。**

**假如浏览器找不到已定义的命名锚，那么就会定位到文档的顶端。不会有错误发生**

## HTML图像

HTML图像是通过\<img>标签进行定义的

```html
<img src="w3school.jpg" width="104" height="142" />
```

### 替换文本属性（Alt）

alt 属性用来为图像定义一串预备的可替换的文本。替换文本属性的值是用户定义的。

```html
<img src="boat.gif" alt="Big Boat">
```

当浏览器无法载入图像时，替换文本属性可告诉读者他们失去的信息。此时，浏览器将显示这个替代性的文本而不是图像。为页面上的图像都加上替换文本属性是个好习惯，这样有助于更好的显示信息，并且对于那些使用纯文本浏览器的人来说是非常有用的。

## HTML图像地图

\<map> 标签用于定义图像地图。图像地图（image map，一种分区导航图）是一种具有可点击区域的图像。
\<map> 元素需要一个name 属性，该属性与元素 的usemap属性相关联，创建图像和地图之间的关系。
\<map> 元素包含一些元素，定义图像地图中的可点击区域。

```html
<img src="life.png" alt="Life" usemap="#lifemap" width="650" height="451">

<map name="lifemap">
  <area shape="rect" coords="10,208,155,338" alt="AirPods" href="airpods.html">
  <area shape="rect" coords="214,65,364,365" alt="iPhone" href="iphone.html">
  <area shape="circle" coords="570,291,75" alt="Coffee" href="coffee.html">
</map>
```

\<area>用于定义图像地图中的可点击区域

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

## HTML格式化

文本格式化标签

|   标签    |      描述      |
| :-------: | :------------: |
|   \<b>    | 定义粗体文本。 |
|  \<big>   |  定义大号字。  |
|   \<em>   | 定义着重文字。 |
|   \<i>    |  定义斜体字。  |
| \<small>  |  定义小号字。  |
| \<strong> | 定义加重语气。 |
|  \<sub>   |  定义下标字。  |
|  \<sup>   |  定义上标字。  |
|  \<ins>   |  定义插入字。  |
|  \<del>   |  定义删除字。  |

“计算机输出”标签

|  标签   |         描述         |
| :-----: | :------------------: |
| \<code> |   定义计算机代码。   |
| \<kbd>  |     定义键盘码。     |
| \<samp> | 定义计算机代码样本。 |
|  \<tt>  |   定义打字机代码。   |
| \<var>  |      定义变量。      |
| \<pre>  |   定义预格式文本。   |

引用、引用和术语定义

| 标签          | 描述               |
| :------------ | :----------------- |
| \<abbr>       | 定义缩写。         |
| \<acronym>    | 定义首字母缩写。   |
| \<address>    | 定义地址。         |
| \<bdo>        | 定义文字方向。     |
| \<blockquote> | 定义长的引用。     |
| \<q>          | 定义短的引用语。   |
| \<cite>       | 定义引用、引证。   |
| \<dfn>        | 定义一个定义项目。 |

## HTML引用

HTML\<q>元素定义**短的引用**
浏览器通常会为\<q>元素包围引号

```html
<p>WWF的目标是:<q>构建人与自然和谐共存的世界。</q></p>
```

HTML\<blockquote>元素定义被引用的节
浏览器通常会对\<blockquote>元素进行缩进处理

```html
<p>以下内容引用自 WWF 的网站：</p>
<blockquote cite="http://www.worldwildlife.org/who/index.html">
五十年来，WWF 一直致力于保护自然界的未来。
世界领先的环保组织，WWF 工作于 100 个国家，
并得到美国一百二十万会员及全球近五百万会员的支持。
</blockquote>
```

HTML\<abbr>元素定义缩写或者首字母缩略语
对缩写进行标记能够为浏览器、翻译系统以及搜索引擎提供有用的信息

```html
<p><abbr title="World Health Organization">WHO</abbr> 成立于 1948 年。</p>
```

HTML\<dfn>元素定义项目或者缩写的定义

```html
<!--1.如果设置了<dfn>元素的title属性，则定义项目:-->
<p><dfn title="World Health Organization">WHO</dfn> 成立于 1948 年。</p>
<!--2.如果<dfn>元素包含具有标题的<abbr>元素，则title定义项目:-->
<p><dfn><abbr title="World Health Organization">WHO</abbr></dfn> 成立于 1948 年。</p>
<!--3.否则，<dfn>文本内容即是项目，并且父元素包含定义:-->
<p><dfn>WHO</dfn> World Health Organization 成立于 1948 年。</p>
```

HTML\<address>元素定义文档或文章的联系信息（作者/拥有者）
此元素通常以斜体显示。大多数浏览器会在此元素前后添加折行。

```html
<address>
Written by Donald Duck.<br> 
Visit us at:<br>
Example.com<br>
Box 564, Disneyland<br>
USA
</address>
```

HTML\<cite>元素定义著作的标题
浏览器通常会以斜体显示\<cite>元素

```html
<p><cite>The Scream</cite> by Edward Munch. Painted in 1893.</p>
```

HTML\<bdo>元素定义双流向覆盖
\<bdo>元素用于覆盖当前文本方向：

```html
<bdo dir="rtl">This text will be written from right to left</bdo>
<!--在浏览器显示：tfel ot thgir morf nettirw eb lliw txet sihT-->
```

## HTML表格

表格由\<table> 标签来定义。每个表格均有若干行（由\<tr>标签定义），每行被分割为若干单元格（由\<td>标签定义）。字母 td 指表格数据，即数据单元格的内容。数据单元格可以包含文本、图片、列表、段落、表单、水平线、表格等等。

```html
<table border="1">
<tr>
<td>row 1, cell 1</td>
<td>row 1, cell 2</td>
</tr>
<tr>
<td>row 2, cell 1</td>
<td>row 2, cell 2</td>
</tr>
</table>
```

在浏览器显示如下：

| row 1, cell 1 | row 1, cell 2 |
| ------------- | ------------- |
| row 2, cell 1 | row 2, cell 2 |

### 表格的表头

表格的表头使用 \<th> 标签进行定义。
大多数浏览器会把表头显示为粗体居中的文本：

```html
<table border="1">
<tr>
<th>Heading</th>
<th>Another Heading</th>
</tr>
<tr>
<td>row 1, cell 1</td>
<td>row 1, cell 2</td>
</tr>
<tr>
<td>row 2, cell 1</td>
<td>row 2, cell 2</td>
</tr>
</table>
```

在浏览器显示如下：

| Heading       | Another Heading |
| ------------- | --------------- |
| row 1, cell 1 | row 1, cell 2   |
| row 2, cell 1 | row 2, cell 2   |

### 表格中的空单元格

在一些浏览器中，没有内容的表格单元显示得不太好。如果某个单元格是空的（没有内容），浏览器可能无法显示出这个单元格的边框。

```html
<table border="1">
<tr>
<td>row 1, cell 1</td>
<td>row 1, cell 2</td>
</tr>
<tr>
<td></td>
<td>row 2, cell 2</td>
</tr>
</table>
```

浏览器可能会这样显示：

![表格中的空单元格](https://www.w3school.com.cn/i/table_td_empty.gif)

**注意：**这个空的单元格的边框没有被显示出来。为了避免这种情况，在单元格中添加一个空格占位符，就可以将边框显示出来

```html
<table border="1">
<tr>
<td>row 1, cell 1</td>
<td>row 1, cell 2</td>
</tr>
<tr>
<td>&nbsp;</td>
<td>row 2, cell 2</td>
</tr>
</table>
```

## HTML列表

### 无序列表

无序列表是一个项目的列表，此列项目使用粗体圆点（典型的小黑圆圈）进行标记。
无序列表始于 \<ul> 标签。每个列表项始于 \<li>。

```html
<ul>
<li>Coffee</li>
<li>Milk</li>
</ul>
```

浏览器显示如下：

- Coffee
- Milk

列表项内部可以使用段落、换行符、图片、链接以及其他列表等等。

### 有序列表

同样，有序列表也是一列项目，列表项目使用数字进行标记。
有序列表始于 \<ol> 标签。每个列表项始于 \<li> 标签。

```html
<ol>
<li>Coffee</li>
<li>Milk</li>
</ol>
```

浏览器显示如下：

1. Coffee
2. Milk

列表项内部可以使用段落、换行符、图片、链接以及其他列表等等。

### 定义列表

自定义列表不仅仅是一列项目，而是项目及其注释的组合。
自定义列表以 \<dl> 标签开始。每个自定义列表项以 \<dt> 开始。每个自定义列表项的定义以 \<dd> 开始。

```html
<dl>
<dt>Coffee</dt>
<dd>Black hot drink</dd>
<dt>Milk</dt>
<dd>White cold drink</dd>
</dl>
```

浏览器显示如下：

Coffee
		Black hot drink
Milk
		White cold drink

定义列表的列表项内部可以使用段落、换行符、图片、链接以及其他列表等等。
