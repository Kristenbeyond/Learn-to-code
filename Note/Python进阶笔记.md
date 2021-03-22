### Python类属性和实例属性的优先级

可以看到，属性可以分为类属性和实例属性，那么问题就来了，如果类属性和实例属性名字相同时，会怎么样，这就涉及Python中类属性和实例属性的优先级的问题了。
我们可以做一个实验，在前面类定义的基础上，在实例属性中，也初始化一个localtion的属性。

```py
class Animal(object):
    localtion = 'Asia'
    def __init__(self, name, age, localtion):
        self.name = name
        self.age = age
        self.localtion = localtion
```

接着我们初始化两个实例，并把localtion打印出来。

```py
dog = Animal('wangwang', 1, 'GuangDong')
cat = Animal('mimi', 3, 'ChongQing')
print(dog.localtion) # ==> GuangDong
print(cat.localtion) # ==> ChongQing
print(Animal.localtion) # ==> Asia
```

那通过实例，可不可以修改类属性呢？我们来尝试一下：

```py
cat.localtion = 'Africa'
print(Animal.localtion) # ==> Asia
```

这里依然打印了Asia，可见通过实例是无法修改类的属性的，事实上，通过实例方法修改类属性，只是给实例绑定了一个对应的实例属性：

```python
# 新增的实例属性
print(cat.localtion) # ==> Africa
```

因此，需要特别注意，尽量不要通过实例来修改类属性，否则很容易引发意想不到的错误。





## Python中的访问限制

并不是所有的属性都可以被外部访问的，这种不能被外部访问的属性称为私有属性。私有属性是以双下划线'__'开头的属性。

```
# 类私有属性
class Animal(object):
    __localtion = 'Asia'

print(Animal.__localtion)

Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: type object 'Animal' has no attribute '__localtion'
```

 

```
# 实例私有属性
class Animal(object):
    def __init__(self, name, age, localtion):
        self.name = name
        self.age = age
        self.__localtion = localtion

dog = Animal('wangwang', 1, 'GuangDong')
print(dog.name) # ==> wangwang
print(dog.age) # ==> 1
print(dog.__localtion)

Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'Animal' object has no attribute '__localtion'
```

在外部访问私有属性将会抛出异常，提示没有这个属性。
虽然私有属性无法从外部访问，但是，从类的内部是可以访问的。私有属性是为了保护类或实例属性不被外部污染而设计的。



## Python定义实例方法

私有属性没有办法从外部访问，只能在类的内部操作；那如果外部需要操作私有属性怎么办？这个时候可以通过定义类或者实例的方法来操作私有属性，本节课先来介绍实例方法。
实例的方法指的就是在类中定义的函数，实例方法的第一个参数永远都是self，self是一个引用，指向调用该方法的实例对象本身，除此以外，其他参数和普通函数是完全一样的。

```
class Person(object):

    def __init__(self, name):
        self.__name = name

    def get_name(self):
        return self.__name
```

在上面的定义，**name是实例的私有属性，从外部是无法访问的，而get_name(self) 就是一个实例方法，在实例方法里面是可以操作私有属性的，注意，它的第一个参数是self。**
**另外，**__init__(self, name)其实也可看做是一个特殊的实例方法。
通过定义get_name(self)方法，在外部就可以通过这个方法访问私有属性了。

```
p = Person('Alice')
print(p.get_name()) # ==> Alice
```

注意，在外部调用实例方法时，是不需要显式传递self参数的。
另外，通过定义实例方法来操作私有属性的这种方法是推荐的，这种数据封装的形式除了能保护内部数据一致性外，还可以简化外部调用的难度。
当然，实例方法并不仅仅是为私有属性服务的，我们可以把和类的实例有关的操作都抽象成实例方法，比如：打印实例的详细信息等等。

```
class Animal(object):
    def __init__(self, name, age, localtion):
        self.name = name
        self.age = age
        self.localtion = localtion

    def get_info(self):
        return 'name = {}, age = {}, localtion = {}'.format(self.name, self.age, self.localtion)

dog = Animal('wangwang', 1, 'GuangDong')
print(dog.get_info())
```



## Python定义类方法

在上一节课，为了操作实例对象的私有属性，我们定义了实例方法；同样的，如果需要需要操作类的私有属性，则应该定义类的方法。
默认的，在class中定义的全部是实例方法，实例方法第一个参数 self 是实例本身。
要在class中定义类方法，需要这么写：

```
class Animal(object):
    __localtion = 'Asia'
    def __init__(self, name, age):
        self.name = name
        self.age = age

    @classmethod
    def set_localtion(cls, localtion):
        cls.__localtion = localtion

    @classmethod
    def get_localtion(cls):
        return cls.__localtion

print(Animal.get_localtion()) # ==> Asia
Animal.set_localtion('Afica')
print(Animal.get_localtion()) # ==> Africa
```

和实例方法不同的是，这里有两点需要特别注意：

1. 类方法需要使用@classmethod来标记为类方法，否则定义的还是实例方法
2. 类方法的第一个参数将传入类本身，通常将参数名命名为 cls，上面的 cls.__localtion 实际上相当于Animal.__localtion。

​    因为是在类上调用，而非实例上调用，因此类方法无法获得任何实例变量，只能获得类的引用。



## Python判断类型

随着我们学习步伐的前进，我们的程序会出现越来越多的类型，有我们自己定义的类，也有Python自有的str、list、dict等，他们的本质都是都是Python中的一种数据类型，这时有必要去判断数据的类型，通过函数isinstance()可以判断一个变量的类型。

```
class Person(object):
    def __init__(self, name, gender):
        self.name = name
        self.gender = gender

class Student(Person):
    def __init__(self, name, gender, score):
        super(Student, self).__init__(name, gender)
        self.score = score

class Teacher(Person):
    def __init__(self, name, gender, course):
        super(Teacher, self).__init__(name, gender)
        self.course = course

p = Person('Tim', 'Male')
s = Student('Bob', 'Male', 88)
t = Teacher('Alice', 'Female', 'English')
```

当我们拿到变量 p、s、t 时，可以使用 isinstance 判断类型：

```
>>> isinstance(p, Person)
True # p是Person类型
>>> isinstance(p, Student)
False # p不是Student类型
>>> isinstance(p, Teacher)
False # p不是Teacher类型
```

这说明在继承链上，一个父类的实例不能是子类类型，因为子类比父类多了一些属性和方法。
我们再考察 s：

```
>>> isinstance(s, Person)
True # s是Person类型
>>> isinstance(s, Student)
True # s是Student类型
>>> isinstance(s, Teacher)
False # s不是Teacher类型
```

s 是Student类型，不是Teacher类型，这很容易理解。但是，s 也是Person类型，因为Student继承自Person，虽然它比Person多了一些属性和方法，但是，把 s 看成Person的实例也是可以的。

这说明在一条继承链上，一个实例可以看成它本身的类型，也可以看成它父类的类型。

isinstance也可以用于Python自有数据类型的判断。

```
s = 'this is a string.'
n = 10
isinstance(s, int) # ==> False
isinstance(n, str) # ==> False
```



## Python中的多态

类具有继承关系，并且子类类型可以向上转型看做父类类型，如果我们从 Person 派生出 Student和Teacher ，并都写了一个who() 方法：

```
class Person(object):
    def __init__(self, name, gender):
        self.name = name
        self.gender = gender
    def who(self):
        return 'I am a Person, my name is %s' % self.name

class Student(Person):
    def __init__(self, name, gender, score):
        super(Student, self).__init__(name, gender)
        self.score = score
    def who(self):
        return 'I am a Student, my name is %s' % self.name

class Teacher(Person):
    def __init__(self, name, gender, course):
        super(Teacher, self).__init__(name, gender)
        self.course = course
    def who(self):
        return 'I am a Teacher, my name is %s' % self.name
```

接着，我们分别把不同类型的who()函数结果打印出来：

```
p = Person('Tim', 'Male')
s = Student('Bob', 'Male', 88)
t = Teacher('Alice', 'Female', 'English')
```

运行结果：

```
I am a Person, my name is Tim
I am a Student, my name is Bob
I am a Teacher, my name is Alice
```

这种行为称为多态。从定义上来讲，Student和Teacher都拥有来自父类Person继承的who()方法，以及自己定义的who()方法。但是在实际调用的时候，会首先查找自身的定义，如果自身有定义，则优先使用自己定义的函数；如果没有定义，则顺着继承链向上找。

```
class Boss(Person):
    def __init__(self, name, gender,company):
        super(Boss, self).__init__(name, gender)
        self.company = company

b = Boss('Bob', 'Male', 'Alibaba')
b.who() # ==> I am a Person, my name is Bob
```

在Boss的定义类，没有定义who方法，所以会顺着继承链向上找到父类的who方法并且调用。



## Python中的多重继承**

除了从一个父类继承外，Python允许从多个父类继承，称为多重继承。多重继承和单继承没有特别大的差异，只是在括号内加入多个需要继承的类的名字即可。

```
class A(object):
    def __init__(self, a):
        print ('init A...')
        self.a = a

class B(A):
    def __init__(self, a):
        super(B, self).__init__(a)
        print ('init B...')

class C(A):
    def __init__(self, a):
        super(C, self).__init__(a)
        print ('init C...')

class D(B, C):
    def __init__(self, a):
        super(D, self).__init__(a)
        print ('init D...')
```

多重继承的继承链就不是一棵树了，它像这样：

![img](https://img.mukewang.com/5f48a2020001015707580552.jpg)

从上图可知，A类被继承了两次，那么A的__init__()方法，是否会被调用两次呢？

```
>>> d = D('d')
init A...
init C...
init B...
init D...
```

实践证明，在多重继承里，A虽然被继承了两次，但是__init__()的方法只调用一次。

**多重继承的目的是从两种继承树中分别选择并继承出子类，以便组合功能使用。**
举个例子，Python的网络服务器有TCPServer、UDPServer、UnixStreamServer、UnixDatagramServer，而服务器运行模式有 多进程ForkingMixin 和 多线程ThreadingMixin两种。
要创建多进程模式的 TCPServer：

```
class MyTCPServer(TCPServer, ForkingMixin)
    pass
```

要创建多线程模式的 UDPServer：

```
class MyUDPServer(UDPServer, ThreadingMixin):
    pass
```

如果没有多重继承，要实现上述所有可能的组合需要 4x2=8 个子类。



## Python类的__str__ 和 __repr__方法

对于Python的内建对象，比如int、dict、list等，通过str()方法，可以把这些对象转换为字符串对象输出。

```
num = 12
str(num) # ==> '12'
d = {1: 1, 2: 2}
str(d) # ==> '{1: 1, 2: 2}'
l = [1,2,3,4,5]
str(l) # ==> '[1, 2, 3, 4, 5]'
```

对于自定义对象，通过str()方法，同样可以得到对象所对应的字符串结果，只不过结果会有些难理解。

```
class Person:
    pass

bob = Person()
str(bob) # ==> '<__main__.Person object at 0x7fc77b859c50>'
```

<__main__.Person object at 0x7fc77b859c50>这个结果其实是Animal的实例cat在内存中的地址，这是相当难以理解的，不过引发思考的是，通过str()打印的数据，是怎么来的呢？
这其实是对象的内建方法__str__返回的。
通过dir()方法，我们可以把对象的所有方法打印出来。

```
>>> dir(list)
['__add__', '__class__', '__contains__', '__delattr__', '__delitem__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__gt__', '__hash__', '__iadd__', '__imul__', '__init__', '__init_subclass__', '__iter__', '__le__', '__len__', '__lt__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__reversed__', '__rmul__', '__setattr__', '__setitem__', '__sizeof__', '__str__', '__subclasshook__', 'append', 'clear', 'copy', 'count', 'extend', 'index', 'insert', 'pop', 'remove', 'reverse', 'sort']
```

可以看到，int、dict、list等的内建对象都实现了自己的__str__()方法，可以把相应的字符串返回，如果我们的类也想把容易理解的字符串输出的话，那么我们也需要实现类的__str__()方法。

```
class Person(object):
    def __init__(self, name, gender):
        self.name = name
        self.gender = gender
    def __str__(self):
        return 'name: {}, gender: {}'.format(self.name, self.gender)

bob = Person('Bob', 'Male')
str(bob) # ==> 'name: Bob, gender: Male'
```

但是，对于直接在终端输入变量bob，得到的依然是这样结果。

```
>>> bob
<__main__.Person object at 0x7fc77b859cc0>
```

而对于int、list等的对象，直接输入变量也可得到可读的结果。

```
>>> num = 12
>>> str(num)
'12'
>>> d = {1: 1, 2: 2}
>>> d
{1: 1, 2: 2}
```

**__str__()函数似乎没有在自定义类Person中生效，这是为什么呢？**
这是因为 Python 定义了__str()__和__repr__()两种方法，__str()__用于显示给用户，而__repr__()用于显示给开发人员，当使用str()时，实际调用的是__str__()方法，而直接输入变量，调用的是__repr__()方法。

```
class Person(object):
    def __init__(self, name, gender):
        self.name = name
        self.gender = gender
    def __str__(self):
        return 'name: {}, gender: {}'.format(self.name, self.gender)
    def __repr__(self):
        return 'name: {}, gender: {}'.format(self.name, self.gender)

bob = Person('Bob', 'Male')
str(bob) # ==> 'name: Bob, gender: Male'
>>> bob
'name: Bob, gender: Male'
```





## Python类的数学运算

事实上，Python很多的操作都是通过内建函数来实现的，比如最熟悉的加减乘除，都是通过内建函数来实现的，分别是`__add__`、`__sub__`、`__mul__`、`__truediv__`。因此，只要我们的自定义类实现了相关的内建函数，我们的类对象，也可以做到加减乘除。
对于有理数，我们可以使用Rational类来表示：

```
class Rational(object):
    def __init__(self, p, q):
        self.p = p
        self.q = q
```

其中，p、q 都是整数，表示有理数 p/q。
如果要让Rational进行加法运算，需要正确实现__add__：

```
class Rational(object):
    def __init__(self, p, q):
        self.p = p
        self.q = q
    def __add__(self, r):
        return Rational(self.p * r.q + self.q * r.p, self.q * r.q)
    def __str__(self):
        return '{}/{}'.format(self.p, self.q)
```

定义好后，就可以尝试一下有理数的加法了：

```
>>> r1 = Rational(1, 2)
>>> r2 = Rational(2, 3)
>>> print(r1 + r2)
7/6
```

需要注意__add__()函数，它有一个参数，表示的是运算的第二个操作数，比如：r1 + r2，那么在__add__()方法中的参数，r指的就是r2，这个参数是运算符重载的时候传递的。
另外，细心的同学可能注意到了，相比加减乘的特殊方法，除法的特殊方法名字较长__truediv__，并且含有true这样的描述，这其实和Python除法是有关系的。
Python的除法可以分为地板除（你没看错，就是地板）和普通除法，地板除的特殊方法是__floordiv__，普通除法是__truediv__。
地板除法和普通除法不一样，地板除法的结果只会向下取整数。

```
>>> num = 5
>>> num.__truediv__(3)
1.6666666666666667
>>> num.__floordiv__(3)
1 # 向下取整
>>> num = 7
>>> num.__floordiv__(3)
2
```

在运算中，普通除法使用/表示，而地板除使用//表示。

```py
>>> 5 / 3
1.6666666666666667
>>> 5 // 3
1
```





## Python类的__slots__方法  //限制属性的动态添加

由于Python是动态语言，任何实例在运行期都可以动态地添加属性。比如：

```
class Student(object):
    def __init__(self, name, gender, score):
        self.name = name
        self.gender = gender
        self.score = score
```

此时，Student类有三个属性，name、gender、score，由于是动态语言，在运行时，可以随意添加属性。

```
student = Student('Bob', 'Male', 99)
student.age = 12 # ==> 动态添加年龄age属性
```

如果要限制添加的属性，例如，Student类只允许添加 name、gender和score 这3个属性，就可以利用Python的一个特殊的__slots__来实现。

```
class Student(object):
    __slots__ = ('name', 'gender', 'score')
    def __init__(self, name, gender, score):
        self.name = name
        self.gender = gender
        self.score = score
```

使用__slots__ = ('name', 'gender', 'score') 限定Student类的属性，这个时候在外部再次添加动态属性age，将会报错。

```
>>> student = Student('Bob', 'Male', 99)
>>> student.age = 12 # ==> 动态添加年龄age属性
Traceback (most recent call last):
AttributeError: 'Student' object has no attribute 'age'
```

__slots__的目的是限制当前类所能拥有的属性，避免因为外部属性的操作导致类属性越来越难以管理。



## Python读取文件

 **读取若干字符**

文件对象提供read()方法，可以读取文件中的若干个字符，它提供一个参数size，可以指定读取字符的数量。

```
s = f.read(5)
print(s) # ==> Hello
```

当read()之后，访问文件的游标就会移动到第六个字符前面，此时，继续read，将得到Hello后面的结果。

```
s = f.read(6)
print(s) # ==> ' World'
```

### **读取一行**

文件对象提供readline()方法，和read()方法类似，可以读取文件中的若干个字符，它也提供一个参数size，可以指定读取字符的数量，不过和read()方法不同的是，readline()方法遇到一行结束的时候，就会返回。

```
f.close()
f = open('test.txt', 'r') # 重新打开文件
s = f.readline(20)
print(s)  # ==> 'Hello World.\n'
```

可以看到，打印的内容并没有20个字符，readline最多返回一行的所有字符。

### **读取多行**

文件对象提供readlines()方法，可以读取多行字符，返回一个列表。它提供一个hint参数，表示指定读取的行数，没有指定则默认以列表的形式返回文件所有的字符串。

```
f.close()
f.open('test.txt', 'r')
s = f.readlines()
print(s) # ==> ['Hello World.\n', 'Hello Python.\n', 'Hello Imooc.\n']
```





## Python往文件追加内容

通过w的打开方式打开文件，会清空文件的内容，这在很多场景下是不合适的，比如写系统日志的时候，需要累积随时间推移的所有数据。

Python提供文件追加内容的打开模式，可以往文件尾部添加内容，又不清空文件原有的内容。

| **模式** | **描述**                                                 |
| -------- | -------------------------------------------------------- |
| a        | 打开一个文件并追加内容，会往文件尾部添加内容             |
| ab       | 以二进制格式打开一个文件并追加内容，会往文件尾部添加内容 |
| a+       | 打开一个文件并使用追加进行读写                           |

 

```
f = open('test.txt', 'a')
f.write('Hello Everyone\n')
f.close()
```

使用a的打开方式打开文件，文件游标默认是在文件的尾部，因此，可以便捷的往文件尾部添加内容，除此以外，文件对象还提供seek()方法，可以移动文件的游标位置，它接受一个参数，表示文件的位置，0：文件首部，1：当前位置，2：文件尾部，通过seek()可以把文件游标移动到文件首部但不删除文件的内容。

```
f = open('test.txt', 'a+')
content = f.readlines()
print(content) # ==> []
f.seek(0)
content = f.readlines()
print(content) # ==> ['Hello World\n', 'Hello Python\n', 'Hello Imooc\n']
```

第一次print(content)的时候，由于文件游标在文件的尾部，所以readlines()读取不到任何数据，打印了空的结果，第二次print(content)的时候，由于通过seek(0)，文件游标移动到了文件的首部，因此readlines()就返回了文件所有的内容。



## Python正确关闭文件

在进行文件操作的时候，正确关闭一个文件非常重要，如果在文件读写后，没有正确关闭一个文件的话，则有可能导致文件损坏，文件内容丢失等问题。

在一般情况下，我们使用文件对象的close()方法，来关闭一个文件。
但是，使用close()方法，也不是100%安全的，如果在close()文件之前，程序异常退出了，那么文件也得不到正确的关闭。比如：

```
f = open('test.txt', 'a+')
exit(-1) # ==> 模拟程序异常退出
f.close() # ==> close语句永远的不到执行
```

在实际工程中，close()文件之前，为了正确关闭文件，需要考虑各种异常情况，这是非常麻烦的一件事，Python提供with关键字，可以免除这类后顾之忧。
with关键字对资源进行访问的场合，会确保不管在使用过程中是否发生异常，都会执行必要的“清理”的操作，释放资源，比如文件使用后自动关闭等等。
with的使用方法如下：

```
with open('test.txt', 'r') as f:
    content = f.readlines()
    for line in content:
        print(line)
```

当文件使用结束后，不需要显式的调用f.close()关闭文件。