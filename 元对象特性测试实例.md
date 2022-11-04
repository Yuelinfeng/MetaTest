# 元对象特性测试实例

## 创建一个基于QWidget的应用程序

- 点击按钮，再文本编辑框内会给出相应的操作结果提示信息
- 使用了Q_CLASSINFO
    - 作用
        - 将额外信息与类相关联
            - example
                
                ```cpp
                class MyClass : public QObject
                {
                    Q_OBJECT
                    Q_CLASSINFO("Author", "Pierre Gendron")
                    Q_CLASSINFO("URL", "http://www.my-organization.qc.ca")
                
                public:
                    ...
                };
                ```
                
        - 可以用QObject::metaObject()得到
            - example
                
                ```cpp
                QMetaProperty prop = meta->property(i);
                const char* propName = prop.name();
                QString propValue = boy->property(propName).toString();
                ui->textEdit->append(QString("属性名称：%1，属性值：%2").arg(propName).arg(propValue));
                ```
                
        - Qt在Active Qt、Qt D-Bus和Qt QML中只有限地使用了这个特性。
    - 使用方法（原型）
        
        ```cpp
        Q_CLASSINFO( Name , Value )
        ```
        
    - 使用：
    
    ```cpp
    Q_CLASSINFO("author","Yuelinfeng")
    Q_CLASSINFO("company","CQUPT")
    Q_CLASSINFO("version","1.0")
    ```
    
- 使用了Q_PROPERTY
    - 作用
        - 用于在继承QObject的类中声明属性
        - 属性的行为类似于类数据成员，但他们具有课通过元对象系统访问的其他功能
    - 原型
        
        ```cpp
        Q_PROPERTY(type name
                   (READ getFunction [WRITE setFunction] |
                    MEMBER memberName [(READ getFunction | WRITE setFunction)])
                   [RESET resetFunction]
                   [NOTIFY notifySignal]
                   [REVISION int]
                   [DESIGNABLE bool]
                   [SCRIPTABLE bool]
                   [STORED bool]
                   [USER bool]
                   [CONSTANT]
                   [FINAL]
                   [REQUIRED])
        ```
        
        - example
            
            ```cpp
            Q_PROPERTY(QString title READ title WRITE setTitle USER true)
            ```
            
        
        详细访问：
        
        [The Property System](https://doc.qt.io/qt-6/properties.html)
        
    - 使用：
        
        ```cpp
        Q_PROPERTY(unsigned age READ age WRITE setAge NOTIFY ageChanged)
        Q_PROPERTY(QString name MEMBER mName)
        Q_PROPERTY(unsigned score MEMBER mScore)
        ```
        
- 使用了信号与槽机制
    - 两种使用方式
        - 第一种，常用，无限制
            
            ```cpp
            QMetaObject::Connection QObject::connect(const QObject *sender, const char *signal,
            																					const QObject *receiver, const char *member,
            																					Qt::ConnectionType = Qt::AutoConnection)
            ```
            
        - 第二种，必须没有重载
            
            ```cpp
            QMetaObject::Connection QObject::connect(const QObject *sender, const QMetaMethod &signal,
            																					const QObject *receivers, const QMetaMethod &method,
            																					Qt::ConnectionType = Qt::AutoConnection)
            ```
            
    - 使用
        
        ```cpp
        connect(ui->spinBoy,SIGNAL(valueChanged(int)),this,SLOT(on_spin_valueChanged(int)));
        ```
        
        ```cpp
        connect(boy, &QPerson::ageChanged, this, &MetaTest::on_ageChanged);
        ```
        
    - 自定义信号和槽函数