### 一、systemd.service

###### 名称

systemd.service — 服务单元配置

###### 大纲

```
*`service`*.service
```



###### 描述

以 "`.service`" 为后缀的单元文件， 封装了一个被 systemd 监视与控制的进程。

本手册列出了所有专用于此类单元的 配置选项(亦称"配置指令"或"单元属性")。 [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#) 中描述了通用于所有单元类型的配置选项， 它们位于 "`[Unit]`" 与 "`[Install]`" 小节。 此类单元专用的配置选项 位于 "`[Service]`" 小节。

其他可用的选项参见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 手册(定义了命令的执行环境)， 以及 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 手册(定义了如何结束进程)， 以及 [systemd.resource-control(5)](https://www.jinbuguo.com/systemd/systemd.resource-control.html#) 手册(定义了进程的 资源控制)。

如果要求启动或停止的某个单元文件 不存在， systemd 将会寻找同名的SysV初始化脚本(去掉 `.service` 后缀)， 并根据那个同名脚本， 动态的创建一个 service 单元。 这主要用于与传统的SysV兼容(不能保证100%兼容)。 更多与SysV的兼容性可参见 [Incompatibilities with SysV](https://www.freedesktop.org/wiki/Software/systemd/Incompatibilities) 文档。



###### 服务模板

**systemd** 服务可以通过 "`*`service`*@*`argument`*.service`" 语法接受一个单独的参数。这样的服务被称为"实例化"服务，而不带 *`argument`* 参数的服务单元定义被称为"模板"。例如 `dhcpcd@.service` 服务模板接受一个网络接口参数之后， 就生成了一个实例化服务。在服务单元模板文件内部， 可以通过 %-specifiers 引用参数(也称为"实例名")。详见 [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#) 手册。



#### 自动依赖



###### 隐含依赖

下列依赖关系是自动隐含的：

- 设置了 `Type=dbus` 的服务会自动添加 `Requires=dbus.socket` 与 `After=dbus.socket` 依赖。
- 基于套接字启动的服务会自动添加对关联的 `.socket` 单元的 `After=` 依赖。 服务单元还会为所有在 `Sockets=` 中列出的 `.socket` 单元自动添加 `Wants=` 与 `After=` 依赖。

还有一些 其他依赖关系是由 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 与 [systemd.resource-control(5)](https://www.jinbuguo.com/systemd/systemd.resource-control.html#) 中的某些资源限制选项自动隐含添加的。



###### 默认依赖

除非明确设置了 `DefaultDependencies=no` ，否则 service 单元将会自动添加下列依赖关系：

- `Requires=sysinit.target`, `After=sysinit.target`, `After=basic.target`, `Conflicts=shutdown.target`, `Before=shutdown.target` 。 这样可以确保普通的服务单元： (1)在基础系统启动完毕之后才开始启动，(2)在关闭系统之前先被干净的停止。 只有那些需要在系统启动的早期就必须启动的服务， 以及那些必须在关机动作的结尾才能停止的服务才需要设置 `DefaultDependencies=no` 。
- 从同一个模版实例化出来的所有服务单元(单元名称中带有 "`@`" 字符)， 默认全部属于与模版同名的同一个 slice 单元(参见 [systemd.slice(5)](https://www.jinbuguo.com/systemd/systemd.slice.html#))。 该同名 slice 一般在系统关机时，与所有模版实例一起停止。 如果你不希望像上面这样，那么可以在模版单元中明确设置 `DefaultDependencies=no` ， 并且：要么在该模版文件中明确定义特定的 slice 单元(同样也要明确设置 `DefaultDependencies=no`)、 要么在该模版文件中明确设置 `Slice=system.slice` (或其他合适的 slice)。 参见 [systemd.resource-control(5)](https://www.jinbuguo.com/systemd/systemd.resource-control.html#) 手册。



#### 选项

每个服务单元文件都必须包含一个 [Service] 小节。 由于此小节中的许多选项也 同时适用于其他类型的单元， 所以本手册仅记录了专用于服务单元的选项。 其他共享的选项参见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#), [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#), [systemd.resource-control(5)](https://www.jinbuguo.com/systemd/systemd.resource-control.html#) 手册。 这里只列出仅能用于 [Service] 小节的 选项(亦称"指令"或"属性")：

- `Type=`

  设置进程的启动类型。必须设为 `simple`, `exec`, `forking`, `oneshot`, `dbus`, `notify`, `idle` 之一：如果设为 `simple` (当设置了 `ExecStart=` 、 但是没有设置 `Type=` 与 `BusName=` 时，这是默认值)， 那么 `ExecStart=` 进程就是该服务的主进程， 并且 systemd 会认为在创建了该服务的主服务进程之后，该服务就已经启动完成。 如果此进程需要为系统中的其他进程提供服务， 那么必须在该服务启动之前先建立好通信渠道(例如套接字)， 这样，在创建主服务进程之后、执行主服务进程之前，即可启动后继单元， 从而加快了后继单元的启动速度。 这就意味着对于 `simple` 类型的服务来说， 即使不能成功调用主服务进程(例如 `User=` 不存在、或者二进制可执行文件不存在)， **systemctl start** 也仍然会执行成功。`exec` 与 `simple` 类似，不同之处在于， 只有在该服务的主服务进程执行完成之后，systemd 才会认为该服务启动完成。 其他后继单元必须一直阻塞到这个时间点之后才能继续启动。换句话说， `simple` 表示当 `fork()` 函数返回时，即算是启动完成，而 `exec` 则表示仅在 `fork()` 与 `execve()` 函数都执行成功时，才算是启动完成。 这就意味着对于 `exec` 类型的服务来说， 如果不能成功调用主服务进程(例如 `User=` 不存在、或者二进制可执行文件不存在)， 那么 **systemctl start** 将会执行失败。如果设为 `forking` ，那么表示 `ExecStart=` 进程将会在启动过程中使用 `fork()` 系统调用。 也就是当所有通信渠道都已建好、启动亦已成功之后，父进程将会退出，而子进程将作为主服务进程继续运行。 这是传统UNIX守护进程的经典做法。 在这种情况下，systemd 会认为在父进程退出之后，该服务就已经启动完成。 如果使用了此种类型，那么建议同时设置 `PIDFile=` 选项，以帮助 systemd 准确可靠的定位该服务的主进程。 systemd 将会在父进程退出之后 立即开始启动后继单元。`oneshot` 与 `simple` 类似，不同之处在于， 只有在该服务的主服务进程退出之后，systemd 才会认为该服务启动完成，才会开始启动后继单元。 此种类型的服务通常需要设置 `RemainAfterExit=` 选项。 当 `Type=` 与 `ExecStart=` 都没有设置时， `Type=``oneshot` 就是默认值。`dbus` 与 `simple` 类似，不同之处在于， 该服务只有获得了 `BusName=` 指定的 D-Bus 名称之后，systemd 才会认为该服务启动完成，才会开始启动后继单元。 设为此类型相当于隐含的依赖于 `dbus.socket` 单元。 当设置了 `BusName=` 时， 此类型就是默认值。`notify` 与 `exec` 类似，不同之处在于， 该服务将会在启动完成之后通过 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 之类的接口发送一个通知消息。systemd 将会在启动后继单元之前， 首先确保该进程已经成功的发送了这个消息。如果设为此类型，那么下文的 `NotifyAccess=` 将只能设为非 `none` 值。如果未设置 `NotifyAccess=` 选项、或者已经被明确设为 `none` ，那么将会被自动强制修改为 `main` 。注意，目前 `Type=``notify` 尚不能与 `PrivateNetwork=``yes` 一起使用。`idle` 与 `simple` 类似，不同之处在于， 服务进程将会被延迟到所有活动任务都完成之后再执行。 这样可以避免控制台上的状态信息与shell脚本的输出混杂在一起。 注意：(1)仅可用于改善控制台输出，切勿将其用于不同单元之间的排序工具； (2)延迟最多不超过5秒， 超时后将无条件的启动服务进程。建议对长时间持续运行的服务尽可能使用 `Type=``simple` (这是最简单和速度最快的选择)。 注意，因为 `simple` 类型的服务 无法报告启动失败、也无法在服务完成初始化后对其他单元进行排序， 所以，当客户端需要通过仅由该服务本身创建的IPC通道(而非由 systemd 创建的套接字或 D-bus 之类)连接到该服务的时候， `simple` 类型并不是最佳选择。在这种情况下， `notify` 或 `dbus`(该服务必须提供 D-Bus 接口) 才是最佳选择， 因为这两种类型都允许服务进程精确的安排 何时算是服务启动成功、何时可以继续启动后继单元。 `notify` 类型需要服务进程明确使用 `sd_notify()` 函数或类似的API， 否则，可以使用 `forking` 作为替代(它支持传统的UNIX服务启动协议)。 最后，如果能够确保服务进程调用成功、服务进程自身不做或只做很少的初始化工作(且不大可能初始化失败)， 那么 `exec` 将是最佳选择。 注意，因为使用任何 `simple` 之外的类型都需要等待服务完成初始化，所以可能会减慢系统启动速度。 因此，应该尽可能避免使用 `simple` 之外的类型(除非必须)。另外，也不建议对长时间持续运行的服务使用 `idle` 或 `oneshot` 类型。

- `RemainAfterExit=`

  当该服务的所有进程全部退出之后， 是否依然将此服务视为活动(active)状态。 默认值为 `no`

- `GuessMainPID=`

  在无法明确定位 该服务主进程的情况下， systemd 是否应该猜测主进程的PID(可能不正确)。 该选项仅在设置了 `Type=forking` 但未设置 `PIDFile=` 的情况下有意义。 如果PID猜测错误， 那么该服务的失败检测与自动重启功能将失效。 默认值为 `yes`

- `PIDFile=`

  该服务PID文件的路径(一般位于 `/run/` 目录下)。 强烈建议在 `Type=``forking` 的情况下明确设置此选项。 如果设为相对路径，那么表示相对于 `/run/` 目录。 systemd 将会在此服务启动完成之后，从此文件中读取主服务进程的PID 。 systemd 不会写入此文件，但会在此服务停止后删除它(若仍然存在)。 PID文件的拥有者不必是特权用户， 但是如果拥有者是非特权用户，那么必须施加如下安全限制： (1)不能是一个指向其他拥有者文件的软连接(无论直接还是间接)； (2)其中的PID必须指向一个属于该服务的进程。

- `BusName=`

  设置与此服务通信 所使用的 D-Bus 名称。 在 `Type=``dbus` 的情况下 必须明确设置此选项。

- `ExecStart=`

  在启动该服务时需要执行的 命令行(命令+参数)。 有关命令行的更多细节， 可参见后文的"命令行"小节。除非 `Type=oneshot` ，否则必须且只能设置一个命令行。 仅在 `Type=oneshot` 的情况下，才可以设置任意个命令行(包括零个)， 多个命令行既可以在同一个 `ExecStart=` 中设置，也可以通过设置多个 `ExecStart=` 来达到相同的效果。 如果设为一个空字符串，那么先前设置的所有命令行都将被清空。 如果不设置任何 `ExecStart=` 指令， 那么必须确保设置了 `RemainAfterExit=yes` 指令，并且至少设置一个 `ExecStop=` 指令。 同时缺少 `ExecStart=` 与 `ExecStop=` 的服务单元是非法的(也就是必须至少明确设置其中之一)。命令行必须以一个可执行文件(要么是绝对路径、要么是不含任何斜线的文件名)开始， 并且其后的那些参数将依次作为"argv[1] argv[2] …"传递给被执行的进程。 可选的，可以在绝对路径前面加上各种不同的前缀表示不同的含义：**表 1. 可执行文件前的特殊前缀**前缀效果"`@`"如果在绝对路径前加上可选的 "`@`" 前缀，那么其后的那些参数将依次作为"argv[0] argv[1] argv[2] …"传递给被执行的进程(注意，argv[0] 是可执行文件本身)。"`-`"如果在绝对路径前加上可选的 "`-`" 前缀，那么即使该进程以失败状态(例如非零的返回值或者出现异常)退出，也会被视为成功退出，但同时会留下错误日志。"`+`"如果在绝对路径前加上可选的 "`+`" 前缀，那么进程将拥有完全的权限(超级用户的特权)，并且 `User=`, `Group=`, `CapabilityBoundingSet=` 选项所设置的权限限制以及 `PrivateDevices=`, `PrivateTmp=` 等文件系统名字空间的配置将被该命令行启动的进程忽略(但仍然对其他 `ExecStart=`, `ExecStop=` 有效)。"`!`"与 "`+`" 类似(进程仍然拥有超级用户的身份)，不同之处在于仅忽略 `User=`, `Group=`, `SupplementaryGroups=` 选项的设置，而例如名字空间之类的其他限制依然有效。注意，当与 `DynamicUser=` 一起使用时，将会在执行该命令之前先动态分配一对 user/group ，然后将身份凭证的切换操作留给进程自己去执行。"`!!`"与 "`!`" 极其相似，仅用于让利用 ambient capability 限制进程权限的单元兼容不支持 ambient capability 的系统(也就是不支持 `AmbientCapabilities=` 选项)。如果在不支持 ambient capability 的系统上使用此前缀，那么 `SystemCallFilter=` 与 `CapabilityBoundingSet=` 将被隐含的自动修改为允许进程自己丢弃 capability 与特权用户的身份(即使原来被配置为禁止这么做)，并且 `AmbientCapabilities=` 选项将会被忽略。此前缀在支持 ambient capability 的系统上完全没有任何效果。 "`@`", "`-`" 以及 "`+`"/"`!`"/"`!!`" 之一，可以按任意顺序同时混合使用。 注意，对于 "`+`", "`!`", "`!!`" 前缀来说，仅能单独使用三者之一，不可混合使用多个。 注意，这些前缀同样也可以用于 `ExecStartPre=`, `ExecStartPost=`, `ExecReload=`, `ExecStop=`, `ExecStopPost=` 这些接受命令行的选项。如果设置了多个命令行， 那么这些命令行将以其在单元文件中出现的顺序依次执行。 如果某个无 "`-`" 前缀的命令行执行失败， 那么剩余的命令行将不会被继续执行， 同时该单元将变为失败(failed)状态。当未设置 `Type=forking` 时， 这里设置的命令行所启动的进程 将被视为该服务的主守护进程。

- `ExecStartPre=`, `ExecStartPost=`

  设置在执行 `ExecStart=` 之前/后执行的命令行。 语法规则与 `ExecStart=` 完全相同。 如果设置了多个命令行， 那么这些命令行将以其在单元文件中出现的顺序 依次执行。如果某个无 "`-`" 前缀的命令行执行失败， 那么剩余的命令行将不会被继续执行， 同时该单元将变为失败(failed)状态。仅在所有无 "`-`" 前缀的 `ExecStartPre=` 命令全部执行成功的前提下， 才会继续执行 `ExecStart=` 命令。`ExecStartPost=` 命令仅在 `ExecStart=` 中的命令已经全部执行成功之后才会运行， 判断的标准基于 `Type=` 选项。 具体说来，对于 `Type=simple` 或 `Type=idle` 就是主进程已经成功启动； 对于 `Type=oneshot` 来说就是最后一个 `ExecStart=` 进程已经成功退出； 对于 `Type=forking` 来说就是初始进程已经成功退出； 对于 `Type=notify` 来说就是已经发送了 "`READY=1`" ； 对于 `Type=dbus` 来说就是已经取得了 `BusName=` 中设置的总线名称。注意，不可将 `ExecStartPre=` 用于 需要长时间执行的进程。 因为所有由 `ExecStartPre=` 派生的子进程 都会在启动 `ExecStart=` 服务进程之前被杀死。注意，如果在服务启动完成之前，任意一个 `ExecStartPre=`, `ExecStart=`, `ExecStartPost=` 中无 "`-`" 前缀的命令执行失败或超时， 那么，`ExecStopPost=` 将会被继续执行，而 `ExecStop=` 则会被跳过。

- `ExecReload=`

  这是一个可选的指令， 用于设置当该服务 被要求重新载入配置时 所执行的命令行。 语法规则与 `ExecStart=` 完全相同。另外，还有一个特殊的环境变量 `$MAINPID` 可用于表示主进程的PID， 例如可以这样使用：`/bin/kill -HUP $MAINPID`注意，像上例那样，通过向守护进程发送复位信号， 强制其重新加载配置文件，并不是一个好习惯。 因为这是一个异步操作， 所以不适用于需要按照特定顺序重新加载配置文件的服务。 我们强烈建议将 `ExecReload=` 设为一个 能够确保重新加载配置文件的操作同步完成的命令行。

- `ExecStop=`

  这是一个可选的指令， 用于设置当该服务被要求停止时所执行的命令行。 语法规则与 `ExecStart=` 完全相同。 执行完此处设置的所有命令行之后，该服务将被视为已经停止， 此时，该服务所有剩余的进程将会根据 `KillMode=` 的设置被杀死(参见 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#))。 如果未设置此选项，那么当此服务被停止时， 该服务的所有进程都将会根据 `KillSignal=` 的设置被立即全部杀死。 与 `ExecReload=` 一样， 也有一个特殊的环境变量 `$MAINPID` 可用于表示主进程的PID 。一般来说，不应该仅仅设置一个结束服务的命令而不等待其完成。 因为当此处设置的命令执行完之后， 剩余的进程会被按照 `KillMode=` 与 `KillSignal=` 的设置立即杀死， 这可能会导致数据丢失。 因此，这里设置的命令必须是同步操作，而不能是异步操作。注意，仅在服务确实启动成功的前提下，才会执行 `ExecStop=` 中设置的命令。 如果服务从未启动或启动失败(例如，任意一个 `ExecStart=`, `ExecStartPre=`, `ExecStartPost=` 中无 "`-`" 前缀的命令执行失败或超时)， 那么 `ExecStop=` 将会被跳过。 如果想要无条件的在服务停止后执行特定的动作，那么应该使用 `ExecStopPost=` 选项。 如果服务启动成功，那么即使主服务进程已经终止(无论是主动退出还是被杀死)，也会继续执行停止操作。 因此停止命令必须正确处理这种场景，如果 systemd 发现在调用停止命令时主服务进程已经终止，那么将会撤销 $MAINPID 变量。重启服务的动作被实现为"先停止、再启动"。所以在重启期间，将会执行 `ExecStop=` 与 `ExecStopPost=` 命令。 推荐将此选项用于那些必须在服务干净退出之前执行的命令(例如还需要继续与主服务进程通信)。当此选项设置的命令被执行的时候，应该假定服务正处于完全正常的运行状态，可以正常的与其通信。 如果想要无条件的在服务停止后"清理尸体"，那么应该使用 `ExecStopPost=` 选项。

- `ExecStopPost=`

  这是一个可选的指令， 用于设置在该服务停止之后所执行的命令行。 语法规则与 `ExecStart=` 完全相同。 注意，与 `ExecStop=` 不同，无论服务是否启动成功， 此选项中设置的命令都会在服务停止后被无条件的执行。应该将此选项用于设置那些无论服务是否启动成功， 都必须在服务停止后无条件执行的清理操作。 此选项设置的命令必须能够正确处理由于服务启动失败而造成的各种残缺不全以及数据不一致的场景。 由于此选项设置的命令在执行时，整个服务的所有进程都已经全部结束， 所以无法与服务进行任何通信。注意，此处设置的所有命令在被调用之后都可以读取如下环境变量： `$SERVICE_RESULT`(服务的最终结果), `$EXIT_CODE`(服务主进程的退出码), `$EXIT_STATUS`(服务主进程的退出状态)。 详见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 手册。

- `RestartSec=`

  设置在重启服务(`Restart=`)前暂停多长时间。 默认值是100毫秒(100ms)。 如果未指定时间单位，那么将视为以秒为单位。 例如设为"20"等价于设为"20s"。

- `TimeoutStartSec=`

  设置该服务允许的最大启动时长。 如果守护进程未能在限定的时长内发出"启动完毕"的信号，那么该服务将被视为启动失败，并会被关闭。 如果未指定时间单位，那么将视为以秒为单位。 例如设为"20"等价于设为"20s"。 设为 "`infinity`" 则表示永不超时。 当 `Type=oneshot` 时， 默认值为 "`infinity`" (永不超时)， 否则默认值等于 `DefaultTimeoutStartSec=` 的值(参见 [systemd-system.conf(5)](https://www.jinbuguo.com/systemd/systemd-system.conf.html#) 手册)。如果一个 `Type=notify` 服务发送了 "`EXTEND_TIMEOUT_USEC=…`" 信号， 那么允许的启动时长将会在 `TimeoutStartSec=` 基础上继续延长指定的时长。 注意，必须在 `TimeoutStartSec=` 用完之前发出第一个延时信号。当启动时间超出 `TimeoutStartSec=` 之后，该服务可以在维持始终不超时的前提下，不断重复发送 "`EXTEND_TIMEOUT_USEC=…`" 信号， 直到完成启动(发送 "`READY=1`" 信号)。详见 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 手册。

- `TimeoutStopSec=`

  此选项有两个用途： (1)设置每个 `ExecStop=` 的超时时长。如果其中之一超时， 那么所有后继的 `ExecStop=` 都会被取消，并且该服务也会被 `SIGTERM` 信号强制关闭。 如果该服务没有设置 `ExecStop=` ，那么该服务将会立即被 `SIGTERM` 信号强制关闭。 (2)设置该服务自身停止的超时时长。如果超时，那么该服务将会立即被 `SIGTERM` 信号强制关闭(参见 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 手册中的 `KillMode=` 选项)。 如果未指定时间单位，那么将视为以秒为单位。 例如设为"20"等价于设为"20s"。 设为 "`infinity`" 则表示永不超时。 默认值等于 `DefaultTimeoutStopSec=` 的值(参见 [systemd-system.conf(5)](https://www.jinbuguo.com/systemd/systemd-system.conf.html#) 手册)。如果一个 `Type=notify` 服务发送了 "`EXTEND_TIMEOUT_USEC=…`" 信号， 那么允许的停止时长将会在 `TimeoutStopSec=` 基础上继续延长指定的时长。 注意，必须在 `TimeoutStopSec=` 用完之前发出第一个延时信号。当停止时间超出 `TimeoutStopSec=` 之后，该服务可以在维持始终不超时的前提下，不断重复发送 "`EXTEND_TIMEOUT_USEC=…`" 信号，直到完成停止。 详见 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 手册。

- `TimeoutSec=`

  一个同时设置 `TimeoutStartSec=` 与 `TimeoutStopSec=` 的快捷方式。

- `RuntimeMaxSec=`

  允许服务持续运行的最大时长。 如果服务持续运行超过了此处限制的时长，那么该服务将会被强制终止，同时将该服务变为失败(failed)状态。 注意，此选项对 `Type=oneshot` 类型的服务无效，因为它们会在启动完成后立即终止。 默认值为 "`infinity`" (不限时长)。如果一个 `Type=notify` 服务发送了 "`EXTEND_TIMEOUT_USEC=…`" 信号， 那么允许的运行时长将会在 `RuntimeMaxSec=` 基础上继续延长指定的时长。 注意，必须在 `RuntimeMaxSec=` 用完之前发出第一个延时信号。当运行时间超出 `RuntimeMaxSec=` 之后，该服务可以在维持始终不超时的前提下，不断重复发送 "`EXTEND_TIMEOUT_USEC=…`" 信号， 直到运行结束(发送 "`STOPPING=1`" 信号或直接退出)。详见 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 手册。

- `WatchdogSec=`

  设置该服务的看门狗(watchdog)的超时时长。 看门狗将在服务成功启动之后被启动。 该服务在运行过程中必须周期性的以 "`WATCHDOG=1`" ("keep-alive ping")调用 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 函数。 如果在两次调用之间的时间间隔大于这里设定的值， 那么该服务将被视为失败(failed)状态， 并会被强制使用 `WatchdogSignal=` 信号(默认为 `SIGABRT`)关闭。 通过将 `Restart=` 设为 `on-failure`, `on-watchdog`, `on-abnormal`, `always` 之一， 可以实现在失败状态下的自动重启该服务。 这里设置的值将会通过 `WATCHDOG_USEC=` 环境变量传递给守护进程， 这样就允许那些支持看门狗的服务自动启用"keep-alive ping"。 如果设置了此选项， 那么 `NotifyAccess=` 将只能设为非 `none` 值。 如果 `NotifyAccess=` 未设置，或者已经被明确设为 `none` ， 那么将会被自动强制修改为 `main` 。 如果未指定时间单位，那么将视为以秒为单位。 例如设为"20"等价于设为"20s"。 默认值"0"表示禁用看门狗功能。 详见 [sd_watchdog_enabled(3)](https://www.jinbuguo.com/systemd/sd_watchdog_enabled.html#) 与 [sd_event_set_watchdog(3)](https://www.jinbuguo.com/systemd/sd_event_set_watchdog.html#) 手册。

- `Restart=`

  当服务进程 正常退出、异常退出、被杀死、超时的时候， 是否重新启动该服务。 所谓"服务进程" 是指 `ExecStart=`, `ExecStartPre=`, `ExecStartPost=`, `ExecStop=`, `ExecStopPost=`, `ExecReload=` 中设置的进程。 当进程是由于 systemd 的正常操作(例如 **systemctl stop|restart**)而被停止时， 该服务不会被重新启动。 所谓"超时"可以是看门狗的"keep-alive ping"超时， 也可以是 **systemctl start|reload|stop** 操作超时。该选项的值可以取 `no`, `on-success`, `on-failure`, `on-abnormal`, `on-watchdog`, `on-abort`, `always` 之一。 `no`(默认值) 表示不会被重启。 `always` 表示会被无条件的重启。 `on-success` 表示仅在服务进程正常退出时重启， 所谓"正常退出"是指：退出码为"0"， 或者进程收到 `SIGHUP`, `SIGINT`, `SIGTERM`, `SIGPIPE` 信号之一， 并且 退出码符合 `SuccessExitStatus=` 的设置。 `on-failure` 表示 仅在服务进程异常退出时重启， 所谓"异常退出" 是指： 退出码不为"0"， 或者 进程被强制杀死(包括 "core dump"以及收到 `SIGHUP`, `SIGINT`, `SIGTERM`, `SIGPIPE` 之外的其他信号)， 或者进程由于 看门狗超时 或者 systemd 的操作超时 而被杀死。**表 2. `Restart=` 的设置分别对应于哪些退出原因**退出原因(↓) | Restart= (→)`no``always``on-success``on-failure``on-abnormal``on-abort``on-watchdog`正常退出 XX  退出码不为"0" X X  进程被强制杀死 X XXX systemd 操作超时 X XX 看门狗超时 X XX X 注意如下例外情况(详见下文)： (1) `RestartPreventExitStatus=` 中列出的退出码或信号永远不会导致该服务被重启。 (2) 被 **systemctl stop** 命令或等价的操作停止的服务永远不会被重启。 (3) `RestartForceExitStatus=` 中列出的退出码或信号将会 无条件的导致该服务被重启。注意，服务的重启频率仍然会受到由 `StartLimitIntervalSec=` 与 `StartLimitBurst=` 定义的启动频率的制约。详见 [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#) 手册。只有在达到启动频率限制之后， 重新启动的服务才会进入失败状态。对于需要长期持续运行的守护进程， 推荐设为 `on-failure` 以增强可用性。 对于自身可以自主选择何时退出的服务， 推荐设为 `on-abnormal`

- `SuccessExitStatus=`

  额外定义其他的进程"正常退出"状态。 也就是，在退出码"0"、以及表示"正常退出"的 `SIGHUP`, `SIGINT`, `SIGTERM`, `SIGPIPE` 信号之外， 再额外添加一组表示"正常退出"的退出码或信号。 可以设为一系列 以空格分隔的数字退出码或者信号名称， 例如：`SuccessExitStatus=1 2 8 SIGKILL`表示当进程的退出码是 1, 2, 8 或被 `SIGKILL` 信号终止时， 都可以视为"正常退出"。如果多次使用此选项， 那么最终的结果将是多个列表的合并。 如果将此选项设为空， 那么先前设置的列表 将被清空。

- `RestartPreventExitStatus=`

  可以设为一系列 以空格分隔的数字退出码或信号名称， 当进程的退出码或收到的信号与此处的设置匹配时， 无论 `Restart=` 选项 是如何设置的， 该服务都将无条件的 禁止重新启动。 例如：`RestartPreventExitStatus=1 6 SIGABRT`可以确保退出码 1, 6 与 `SIGABRT` 信号 不会导致该服务被自动重启。 默认值为空， 表示完全遵守 `Restart=` 的设置。 如果多次使用此选项，那么最终的结果将是多个列表的合并。 如果将此选项设为空，那么先前设置的列表将被清空。

- `RestartForceExitStatus=`

  可以设为一系列以空格分隔的数字退出码或信号名称， 当进程的退出码或收到的信号与此处的设置匹配时， 无论 `Restart=` 是如何设置的，该服务都将无条件的被自动重新启动。 默认值为空，表示完全遵守 `Restart=` 的设置。 如果多次使用此选项，那么最终的结果将是多个列表的合并。 如果将此选项设为空，那么先前设置的列表将被清空。

- `RootDirectoryStartOnly=`

  接受一个布尔值。 设为 yes 表示根目录 `RootDirectory=` 选项(参见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 手册) 仅对 `ExecStart=` 中的程序有效， 而对 `ExecStartPre=`, `ExecStartPost=`, `ExecReload=`, `ExecStop=`, `ExecStopPost=` 中的程序无效。 默认值 no 表示根目录对所有 `Exec*=` 系列选项中的程序都有效。

- `NonBlocking=`

  是否为所有基于套接字启动传递的文件描述符设置非阻塞标记(`O_NONBLOCK`)。 设为 yes 表示除了通过 `FileDescriptorStoreMax=` 引入的文件描述符之外， 所有 ≥3 的文件描述符(非 stdin, stdout, stderr 文件描述符)都将被设为非阻塞模式。 该选项仅在与 socket 单元 ([systemd.socket(5)](https://www.jinbuguo.com/systemd/systemd.socket.html#)) 联用的时候才有意义。 对于那些先前已经通过 `FileDescriptorStoreMax=` 引入的文件描述符则毫无影响。 默认值为 no

- `NotifyAccess=`

  设置通过 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 访问服务状态通知套接字的模式。 可以设为 `none`(默认值), `main`, `exec`, `all` 之一。 `none` 表示不更新任何守护进程的状态，忽略所有状态更新消息。 `main` 表示仅接受主进程的状态更新消息。 `exec` 表示仅接受主进程以及 `Exec*=` 进程的状态更新消息。 `all` 表示接受该服务cgroup内所有进程的状态更新消息。 当设置了 `Type=notify` 或 `WatchdogSec=` 的时候(见前文)，此选项将只能设为非 `none` 值。 如果 `NotifyAccess=` 未设置，或者已经被明确设为 `none` ， 那么将会被自动强制修改为 `main` 。注意，服务单元的 `sd_notify()` 通知能够正常工作的前提， 是必须满足如下两个条件之一： (1)在 PID=1 的进程处理通知消息时，发送该通知的进程依然在运行； (2)发送该通知的进程是 systemd 派生的子进程(也就是匹配 `main` 或 `exec` 的进程)。 如果服务单元中的某个辅助进程在发送了 `sd_notify()` 通知之后就立即退出了， 那么 systemd 将有可能来不及将该通知关联到这个服务单元上。 在这种情况下，即使明确设置了 `NotifyAccess=all` ， 该通知也可能会被忽略掉。

- `Sockets=`

  设置一个 socket 单元的名称， 表示该服务在启动时应当从它继承套接字文件描述符。 通常并不需要明确设置此选项， 因为所有与该服务同名(不算后缀)的 socket 单元的套接字文件描述符， 都会被自动的 传递给派生进程。注意： (1)同一个套接字文件描述符可以被传递给多个不同的进程(服务)。 (2)当套接字上有流量进入时， 被启动的可能是另一个不同于该服务的其他服务。 换句话说就是： 套接字单元中的 `Sockets=` 所指向的服务单元中的 `Sockets=` 未必要反向指回去。如果多次使用此选项， 那么最终的结果将是多个socket单元的合集。 如果将此选项设为空， 那么先前设置的所有socket单元 都将被清空。

- `FileDescriptorStoreMax=`

  允许在 systemd 中最多为该服务存储多少个使用 "`FDSTORE=1`" 消息([sd_pid_notify_with_fds(3)](https://www.jinbuguo.com/systemd/sd_pid_notify_with_fds.html#)) 的文件描述符。默认值为"0"(不存储)。 通过将服务重启过程中不应该关闭的套接字与文件描述符使用这种方法保存起来， 就可以实现让服务在重启(正常重启或崩溃重启)之后不丢失其状态。 进程的状态可以被序列化为一个文件之后保存在 `/run` 中， 或者保存在一个 [memfd_create(2)](http://man7.org/linux/man-pages/man2/memfd_create.2.html) 内存文件描述符中(这是更好的选择)。 所有被 systemd 暂存的文件描述符都将在该服务重启之后交还给该服务的主进程。 所有被 systemd 暂存的文件描述符都将在遇到如下两种情况时被自动关闭： (1)收到 `POLLHUP` 或 `POLLERR` 信号； (2)该服务被彻底停止，并且没有任何剩余的任务需要处理。 如果使用了此选项，那么前文的 `NotifyAccess=` 应该被设为允许访问 systemd 提供的通知套接字。若未设置 `NotifyAccess=` ，那么将被隐含的设为 `main`

- `USBFunctionDescriptors=`

  设为一个包含 [USB FunctionFS](https://www.kernel.org/doc/Documentation/usb/functionfs.txt) 描述符的文件路径， 以实现 USB gadget 支持。 仅与配置了 `ListenUSBFunction=` 的 socket 单元一起使用。该文件的内容将被写入 `ep0` 文件。

- `USBFunctionStrings=`

  设为一个包含 [USB FunctionFS](https://www.kernel.org/doc/Documentation/usb/functionfs.txt) 字符串的文件路径。 其行为与上面的 `USBFunctionDescriptors=` 类似。

参见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 与 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 手册，以了解更多其他选项。



命令行

本小节 讲解 `ExecStart=`, `ExecStartPre=`, `ExecStartPost=`, `ExecReload=`, `ExecStop=`, `ExecStopPost=` 选项的命令行解析规则。

如果要一次设置多个命令，那么可以使用分号(;)将多个命令行连接起来。 注意，仅在设置了 `Type=oneshot` 的前提下，才可以一次设置多个命令。 分号自身 必须用 "`\;`" 表示。

每个命令行的内部 都以空格分隔， 第一项是要运行的命令， 随后的各项则是命令的参数。 每一项的边界都可以用单引号或双引号界定， 但引号自身最终将会被剥离。 还可以使用C语言风格的转义序列， 但仅可使用下文表格中的转义序列。 最后，行尾的反斜杠("`\`") 将被视作续行符(借鉴了bash续行语法)。

命令行的语法刻意借鉴了shell中的转义字符与变量展开语法， 但两者并不完全相同。 特别的， 重定向("`<`", "`<<`", "`>`", "`>>`")、 管道("`|`")、 后台运行("`&`")， 以及*其他下文未明确提及的符号*都不被支持。

要运行的命令(第一项)可以包含空格，但是不能包含控制字符。

可以在各项命令参数中使用 "`%`" 系列替换标记(详见 [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#)手册)。

支持 "`${FOO}`" 与 "`$FOO`" 两种不同的环境变量替换方式。 具体说来就是： "`${FOO}`" 的内容将原封不动的转化为一个单独的命令行参数， 无论其中是否包含空格与引号，也无论它是否为空。 "`$FOO`" 的内容将被原封不动的插入命令行中， 但对插入内容的解释却遵守一般的命令行解析规则。 后文的两个例子， 将能清晰的体现两者的差别。

如果要运行的命令(第一项)不是一个绝对路径， 那么将会在编译时设定的可执行文件搜索目录中查找。 因为默认包括 `/usr/local/bin/`, `/usr/bin/`, `/bin/`, `/usr/local/sbin/`, `/usr/sbin/`, `/sbin/` 目录， 所以可以安全的直接使用"标准目录"中的可执行程序名称(没必要再使用绝对路径)， 而对于非标准目录中的可执行程序，则必须使用绝对路径。建议始终使用绝对路径以避免歧义。 [提示]可以使用 **systemd-path search-binaries-default** 显示编译时设定的可执行文件搜索目录。

例(1)：

```
Environment="ONE=one" 'TWO=two two'
ExecStart=echo $ONE $TWO ${TWO}
```

这将给 **/bin/echo** 命令依次传递如下四个参数: "`one`", "`two`", "`two`", "`two two`"

例(2)：

```
Environment=ONE='one' "TWO='two two' too" THREE=
ExecStart=/bin/echo ${ONE} ${TWO} ${THREE}
ExecStart=/bin/echo $ONE $TWO $THREE
```

这将导致 `/bin/echo` 被执行两次。 第一次被依次传递如下三个参数： "`'one'`", "`'two two' too`", "``" ； 第二次被依次传递如下三个参数： "`one`", "`two two`", "`too`" 。

此外，如果想要传递美元符号($)自身， 则必须使用 "`$$`" 。 而那些无法在替换时确定内容的变量将被当做空字符串。 注意，不可以在第一项(也就是命令的绝对路径)中使用变量替换。

注意，这里使用的变量必须已经在 `Environment=` 或 `EnvironmentFile=` 中定义。 此外，在 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 手册的"环境变量"小节中列出的"静态变量"也可以使用。 例如 `$USER` 就是一个"静态变量"， 而 `$TERM` 则不是。

注意， 这里的命令行并不直接支持shell命令， 但是可以通过模仿下面这个变通的方法来实现：

```
ExecStart=sh -c 'dmesg | tac'
```

例一

```
ExecStart=echo one ; echo "two two"
```

这将导致 **echo** 被执行两次。 第一次被传递了单独一个 "`one`" 参数； 第二次被传递了单独一个 "`two two`" 参数。 因为一次设置了多个命令，所以仅能用于 `Type=oneshot` 类型。

例二

```
ExecStart=echo / >/dev/null & \; \
ls
```

这表示向 **echo** 命令传递五个参数： "`/`", "`>/dev/null`", "`&`", "`;`", "`ls`"



**表 3. 可以在命令行与环境变量中使用的C语言风格的转义序列**

| 转义序列     | 实际含义                       |
| ------------ | ------------------------------ |
| "`\a`"       | 响铃                           |
| "`\b`"       | 退格                           |
| "`\f`"       | 换页                           |
| "`\n`"       | 换行                           |
| "`\r`"       | 回车                           |
| "`\t`"       | 制表符                         |
| "`\v`"       | 纵向制表符                     |
| "`\\`"       | 反斜线                         |
| "`\"`"       | 双引号                         |
| "`\'`"       | 单引号                         |
| "`\s`"       | 空白                           |
| "`\x*`xx`*`" | 十六进制数 *`xx`* 所对应的字符 |
| "`\*`nnn`*`" | 八进制数 *`nnn`* 所对应的字符  |





#### 例子

###### 

**例 1. 简单服务**

下面的单元文件创建了一个运行 `/usr/sbin/foo-daemon` 守护进程的服务。 未设置 `Type=` 等价于 `Type=``simple` 默认设置。 systemd 执行守护进程之后， 即认为该单元已经启动成功。

```
[Unit]
Description=简单的Foo服务

[Service]
ExecStart=/usr/sbin/foo-daemon

[Install]
WantedBy=multi-user.target
```

注意，本例中的 `/usr/sbin/foo-daemon` 必须在启动后持续运行到服务被停止。 如果该进程只是为了派生守护进程，那么应该使用 `Type=``forking`

因为没有设置 `ExecStop=` 选项， 所以在停止服务时，systemd 将会直接向该服务启动的所有进程发送 SIGTERM 信号。 若超过指定时间依然存在未被杀死的进程，那么将会继续发送 SIGKILL 信号。 详见 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 手册。

默认的 `Type=``simple` 并不包含任何通知机制(例如通知"服务启动成功")。 要想使用通知机制，应该将 `Type=` 设为其他非默认值： `Type=``notify` 可用于能够理解 systemd 通知协议的服务； `Type=``forking` 可用于能将自身切换到后台的服务； `Type=``dbus` 可用于能够在完成初始化之后 获得一个 D-Bus 名称的单元。





**例 2. 一次性服务**

`Type=``oneshot` 用于那些只需要执行一次性动作而不需要持久运行的单元， 例如文件系统检查或者清理临时文件。 此类单元， 将会在启动后一直等待指定的动作完成， 然后再回到停止状态。 下面是一个执行清理动作的单元：

```
[Unit]
Description=清理老旧的 Foo 数据

[Service]
Type=oneshot
ExecStart=/usr/sbin/foo-cleanup

[Install]
WantedBy=multi-user.target
```

注意，在 `/usr/sbin/foo-cleanup` 执行结束前， 该服务一直处于"启动中"(activating)状态，而一旦执行结束，该服务又立即变为"停止"(inactive)状态。 也就是说，对于 `Type=``oneshot` 类型的服务，不存在"活动"(active)状态。 这意味着，如果再一次启动该服务，将会再一次执行该服务定义的动作。 注意，在先后顺序上晚于该服务的单元， 将会一直等到该服务变成"停止"(inactive)状态后， 才会开始启动。

`Type=``oneshot` 是唯一可以设置多个 `ExecStart=` 指令的服务类型。 多个 `ExecStart=` 指令将按照它们出现的顺序依次执行， 一旦遇到错误，就会立即停止，不再继续执行， 同时该服务也将进入"失败"(failed)状态。





**例 3. 可停止的一次性服务**

有时候， 单元需要执行一个程序以完成某个设置(启动)， 然后又需要再执行另一个程序以撤消先前的设置(停止)， 而在设置持续有效的时段中，该单元应该视为处于"活动"(active)状态， 但实际上并无任何程序在持续运行。 网络配置服务就是一个典型的例子。 此外，只能启动一次(不可多次启动)的一次性服务， 也是一个例子。

可以通过设置 `RemainAfterExit=``yes` 来满足这种需求。 在这种情况下，systemd 将会在启动成功后将该单元视为处于"活动"(active)状态(而不是"停止"(inactive)状态)。 `RemainAfterExit=``yes` 虽然可以用于所有 `Type=` 类型， 但是在实践中主要用于 `Type=``oneshot` 和 `Type=``simple` 类型。 对于 `Type=``oneshot` 类型， systemd 一直等到服务启动成功之后，才会将该服务置于"活动"(active)状态。 所以，依赖于该服务的其他单元必须等待该服务启动成功之后，才能启动。 但是对于 `Type=``simple` 类型， 依赖于该服务的其他单元无需等待， 将会和该服务同时并行启动。 下面的类似展示了一个简单的静态防火墙服务：

```
[Unit]
Description=简单的静态防火墙

[Service]
Type=oneshot
RemainAfterExit=yes
ExecStart=/usr/local/sbin/simple-firewall-start
ExecStop=/usr/local/sbin/simple-firewall-stop

[Install]
WantedBy=multi-user.target
```

因为服务启动成功后一直处于"活动"(active)状态， 所以再次执行 **systemctl start** 命令不会有任何效果。





**例 4. 传统的服务**

多数传统的守护进程(服务)在启动时会转入后台运行。 systemd 通过 `Type=``forking` 来支持这种工作方式。 对于这种类型的服务，如果最初启动的进程尚未退出， 那么该单元将依然处于"启动中"(activating)状态。 当最初的进程成功退出， 并且至少有一个进程仍然在运行(并且 `RemainAfterExit=``no`)， 该服务才会被视为处于"活动"(active)状态。

对于单进程的传统服务，当最初的进程成功退出后， 将会只剩单独一个进程仍然在持续运行， systemd 将会把这个唯一剩余的进程视为该服务的主进程。 仅在这种情况下，才将可以在 `ExecReload=`, `ExecStop=` … 之类的选项中使用 `$MAINPID` 变量。

对于多进程的传统服务，当最初的进程成功退出后，将会剩余多个进程在持续运行， 因此，systemd 无法确定哪一个进程才是该服务的主进程。 在这种情况下，不可以使用 `$MAINPID` 变量。 然而，如果主进程会创建传统的PID文件， 那么应该将 `PIDFile=` 设为此PID文件的绝对路径， 以帮助 systemd 从该PID文件中读取主进程的PID，从而帮助确定该服务的主进程。 注意，守护进程必须在完成初始化之前写入PID文件， 否则可能会导致 systemd 读取失败 (读取时文件不存在)。

下面是一个 单进程传统服务的示例：

```
[Unit]
Description=一个单进程传统服务

[Service]
Type=forking
ExecStart=/usr/sbin/my-simple-daemon -d

[Install]
WantedBy=multi-user.target
```

参见 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 以了解如何 结束服务进程。





**例 5. DBus 服务**

对于需要在 D-Bus 系统总线上注册一个名字的服务， 应该使用 `Type=``dbus` 并且设置相应的 `BusName=` 值。 该服务不可以派生任何子进程。 一旦从 D-Bus 系统总线成功获取所需的名字，该服务即被视为初始化成功。 下面是一个典型的 D-Bus 服务：

```
[Unit]
Description=一个简单的 DBus 服务

[Service]
Type=dbus
BusName=org.example.simple-dbus-service
ExecStart=/usr/sbin/simple-dbus-service

[Install]
WantedBy=multi-user.target
```

对于*基于 D-Bus 启动*的服务 来说， 不可以包含 "`[Install]`" 小节， 而是应该在对应的 D-Bus service 文件中设置 `SystemdService=` 选项，例如 (`/usr/share/dbus-1/system-services/org.example.simple-dbus-service.service`):

```
[D-BUS Service]
Name=org.example.simple-dbus-service
Exec=/usr/sbin/simple-dbus-service
User=root
SystemdService=simple-dbus-service.service
```

参见 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 手册以了解如何 结束服务进程。





**例 6. 能够通知初始化已完成的服务**

`Type=``simple` 类型的服务 非常容易编写， 但是， 无法向 systemd 及时通知 "启动成功"的消息， 是一个重大缺陷。 `Type=``notify` 可以弥补该缺陷， 它支持将"启动成功"的消息及时通知给 systemd 。 下面是一个典型的例子：

```
[Unit]
Description=Simple notifying service

[Service]
Type=notify
ExecStart=/usr/sbin/simple-notifying-service

[Install]
WantedBy=multi-user.target
```

注意， 该守护进程必须支持 systemd 通知协议， 否则 systemd 将会认为该服务一直处于"启动中"(activating)状态，并在超时后将其杀死。 关于如何支持该通知协议，参见 [sd_notify(3)](https://www.jinbuguo.com/systemd/sd_notify.html#) 手册。

参见 [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#) 手册以了解如何 结束服务进程。





#### 参见

[systemd(1)](https://www.jinbuguo.com/systemd/systemd.html#), [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#), [systemd-system.conf(5)](https://www.jinbuguo.com/systemd/systemd-system.conf.html#), [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#), [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#), [systemd.resource-control(5)](https://www.jinbuguo.com/systemd/systemd.resource-control.html#), [systemd.kill(5)](https://www.jinbuguo.com/systemd/systemd.kill.html#), [systemd.directives(7)](https://www.jinbuguo.com/systemd/systemd.directives.html#)

### 二、systemd.timer

###### 名称

systemd.timer — 定时器单元配置

###### 大纲

```
*`timer`*.timer
```



###### 描述

以 "`.timer`" 为后缀的单元文件， 封装了一个由 systemd 管理的定时器， 以支持基于定时器的启动。

本手册列出了 所有专用于此类单元的配置选项(亦称"配置指令"或"单元属性")。 [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#) 中描述了通用于所有单元类型的配置选项， 它们位于 [Unit] 与 [Install] 小节。 此类单元专用的配置选项位于 [Timer] 小节。

每个定时器单元都必须有一个与其匹配的单元， 用于在特定的时间启动。 匹配的单元可以通过 `Unit=` 选项(见下文)明确指定。 若未指定，则默认是与该单元名称相同的 .service 单元(不算后缀)。例如 `foo.timer` 默认匹配 `foo.service` 单元。

注意，如果在启动时间点到来的时候，匹配的单元已经被启动， 那么将不执行任何动作，也不会启动任何新的服务实例。 因此，那些设置了 `RemainAfterExit=yes`(当该服务的所有进程全部退出之后，依然将此服务视为处于活动状态) 的服务单元一般不适合使用基于定时器的启动。 因为这样的单元仅会被启动一次，然后就永远处于活动(active)状态了。



#### 自动依赖



###### 隐含依赖

下列依赖关系是自动隐含的：

- 定时器单元自动获得对匹配单元的 `Before=` 依赖。



###### 默认依赖

除非明确设置了 `DefaultDependencies=no` ，否则 timer 单元将会自动添加下列依赖关系：

- `Requires=sysinit.target`, `After=sysinit.target`, `Before=timers.target` 依赖； 以及 `Conflicts=shutdown.target`, `Before=shutdown.target` 依赖(确保在关机前干净的停止)。 只有那些在系统启动的早期就必须启动的定时器，以及那些必须在关机动作的结尾才能停止的定时器才需要设置 `DefaultDependencies=no` 。
- 如果在 timer 单元中设置了至少一个 `OnCalendar=` 选项， 那么将会自动获得 `After=time-sync.target` 依赖， 以避免在系统时间尚未正确设置的情况下启动定时器。



#### 选项

定时器单元文件中必须包含一个 [Timer] 小节， 其中包含了该单元所定义的定时器的相关信息。 这里只列出仅能用于 [Timer] 小节的选项(亦称"指令"或"属性")：

- `OnActiveSec=`, `OnBootSec=`, `OnStartupSec=`, `OnUnitActiveSec=`, `OnUnitInactiveSec=`

  定义相对于特定时间点之后一段时间的 单调定时器： `OnActiveSec=` 相对于该单元自身被启动的时间点； `OnBootSec=` 相对于机器被启动的时间点， 也就是内核开始运行的时间点； `OnStartupSec=` 相对于 systemd 被首次启动的时间点，也就是内核启动init进程的时间点； `OnUnitActiveSec=` 相对于匹配单元最后一次被启动的时间点； `OnUnitInactiveSec=` 相对于匹配单元 最后一次被停止的时间点；可以组合使用这些指令(既可以将某个指令使用多次，也可以将多个指令一起使用)， 例如，通过同时使用 `OnBootSec=` 与 `OnUnitActiveSec=` 指令， 就可以实现在系统启动后的某个时间点启动匹配单元， 并且之后每隔一段时间周期性的反复启动匹配单元。指令的值是一个时间长度， 可以使用下面的时间单位后缀：us(微秒), ms(毫秒), s(秒), m(分), h(时), d(天), w(周) 。 如果省略了时间单位，那么表示使用默认单位"秒"。 可以同时使用多个时间单位，例如 "OnBootSec=5h 30min" 表示系统启动之后的5小时30分钟。 更多有关表示时间长度的语法，参见 [systemd.time(7)](https://www.jinbuguo.com/systemd/systemd.time.html#) 手册。如果定时器单元在启动时已经超过了 `OnBootSec=` 或 `OnStartupSec=` 指定的时间， 那么将会立即启动匹配的单元。 但是对于使用其他指令定义的定时器， 超过了就等于错过了，不会尝试去补救。这几个指令定义的定时器都是基于单调时间的单调定时器(monotonic timer)，所谓"单调时间"的意思是从开机那一刻(零点)起， 只要系统正在运行，该时间就不断的单调均匀递增(但在系统休眠时此时间保持不变)，永远不会往后退，并且与时区也没有关系。 即使在系统运行的过程中，用户向前/向后修改系统时间，也不会对"单调时间"产生任何影响。如果给某个指令赋予一个空字符串， 则表示 撤销该指令之前已设置的所有定时器。注意， 这些指令设置的定时器并不必然在所设置的精准时间点上启动匹配单元， 因为它们还受到下文 `AccuracySec=` 选项的影响。

- `OnCalendar=`

  定义基于挂钟时间(wallclock)的日历定时器，值是一个日历事件表达式， 这是与传统cron任务类似的定时器。详见 [systemd.time(7)](https://www.jinbuguo.com/systemd/systemd.time.html#) 手册以了解日历事件表达式的语法。如果定时器单元在启动时已经超过了该指令设置的某个触发时间，那么错过就错过了，不会尝试去补救，只能等待下一个触发时间。可以多次使用此指令以设置多个定时器，如果被赋予了一个空字符串，则表示撤销该指令之前已设置的所有定时器。 该指令定义的定时器是基于挂钟时间(wallclock)的，所谓"挂钟时间"是指真实世界中墙上挂钟的时间，在操作系统中实际上就是系统时间，这个时间是操作系统在启动时从主板的时钟芯片中读取的， 在系统的运行过程中，时间同步服务会不断的根据NTP时间服务器提供的时间对系统时间进行校准，而系统管理员也可能会手动的向前/向后修改系统时间，所以，这个时间既不一定是单调递增的、也不一定是均匀递增的。注意，该指令设置的定时器 并不必然在所设置的精准时间点上启动匹配单元， 因为它们还受到下文 `AccuracySec=` 选项的影响。可以多次设置此选项。

- `AccuracySec=`

  设置定时器的触发精度。默认值是一分钟。定时器并不必然在所设置的精准时间点上启动匹配单元， 而是在所设置的精准时间点为起点的一小段时间窗口范围内的某个时间点上启动匹配单元， 这个时间窗口的起点由 `OnCalendar=`, `OnActiveSec=`, `OnBootSec=`, `OnStartupSec=`, `OnUnitActiveSec=`, `OnUnitInactiveSec=` 决定， 而这个时间窗口的长度则由该指令决定。 在这个时间窗口内，触发点的具体位置虽然无法在系统开机之前预知， 也就是说触发点的具体位置在每次启动之间是随机的， 但是一旦开机之后，对于正在运行中的系统而言又是固定的， 并且对全系统范围内所有的定时器而言都是固定的。 这么做的目的在于避免过多不必要的CPU唤醒，以节约电力。 若想获得最高精度，可以将此选项设为"1us"(一微秒)，但是耗电量就可能明显增加。 注意，定时器的精度还受到 [systemd-system.conf(5)](https://www.jinbuguo.com/systemd/systemd-system.conf.html#) 中的 `TimerSlackNSec=` 选项的影响(不过一般可以忽略不计，参见 [prctl(2)](http://man7.org/linux/man-pages/man2/prctl.2.html) 手册)。 为了优化耗电量， 应该将此指令设为可接收的最大值。

- `RandomizedDelaySec=`

  将此单元的定时器随机延迟一小段时间， 这一小段时间的长度 介于零到该指令设置的时间长度之间， 以均匀概率分布。 默认值是零，表示不延迟。 定时器单元在每次迭代前确定这个随机值的大小， 并简单的把它加到下一次启动匹配单元的时间点上， 此选项可以将大量在同一时间点触发的定时器 均匀的分摊到一小段时间范围内触发， 以避免造成资源争抢。 `AccuracySec=` 允许将一段时间内分散的定时器事件集中到一点，以减少CPU唤醒。 而本指令正好相反， 允许将集中在一点的定时器事件分散到一小段时间范围内， 以避免造成资源争抢。如果同时使用 `RandomizedDelaySec=` 与 `AccuracySec=` 选项， 那么首先添加一个随机的时间， 然后结果可能进一步被平移， 以和系统上其他定时器事件合并。 因为默认设置 `AccuracySec=1min`, `RandomizedDelaySec=0` 鼓励将多个定时器事件聚合在一起。 所以如果希望尽可能均匀分散定时器事件，那么应该将 `RandomizedDelaySec=` 设为一个较大的值，同时设置 `AccuracySec=1us`

- `Unit=`

  该定时器单元的匹配单元， 也就是要被该定时器启动的单元。参数是一个不以 "`.timer`" 结尾的单元名。 默认值是 与此定时器单元同名的服务单元(见上文)。 建议将定时器单元的名字 与被该定时器启动的匹配单元的名字保持一致 (也就是仅单元后缀名不同)。

- `Persistent=`

  此选项仅对 `OnCalendar=` 指令定义的日历定时器有意义。 若设为"yes"，则表示将匹配单元的上次触发时间永久保存在磁盘上。 这样，当定时器单元再次被启动时， 如果匹配单元本应该在定时器单元停止期间至少被启动一次， 那么将立即启动匹配单元。 这样就不会因为关机而错过必须执行的任务。 默认值为 `no`

- `WakeSystem=`

  若设为"yes"， 则表示当某个定时器到达触发时间点时， 唤醒正在休眠的系统并阻止系统进入休眠状态。 注意， 此选项仅确保唤醒系统， 而不关心任务执行完成之后是否需要再次休眠系统。 默认值为 `no`

- `RemainAfterElapse=`

  接受一个布尔值。 若设为"yes"(默认值)， 则表示保持已过期定时器单元的已加载(loaded)状态，并且依然允许查询其状态。 若设为"no"，则表示卸载已过期并且将来也不会被继续触发的定时器单元。 对于那些仅需要临时执行一次、随后即被丢弃的定时器单元来说，设为"no"是首选。 但是需要注意， 对于那些仅需要触发一次的定时器单元来说， 如果 `RemainAfterElapse=yes` ， 那么该定时器将不会被再次触发，也就是可以确保仅被触发一次； 如果 `RemainAfterElapse=no` ， 那么该定时器就有可能会被再次触发，也就是有可能被多次触发。 所以将此选项设为"no"时应该特别小心谨慎。 默认值为 `yes`



#### 参见

[systemd(1)](https://www.jinbuguo.com/systemd/systemd.html#), [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#), [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#), [systemd.service(5)](https://www.jinbuguo.com/systemd/systemd.service.html#), [systemd.time(7)](https://www.jinbuguo.com/systemd/systemd.time.html#), [systemd.directives(7)](https://www.jinbuguo.com/systemd/systemd.directives.html#), [systemd-system.conf(5)](https://www.jinbuguo.com/systemd/systemd-system.conf.html#), [prctl(2)](http://man7.org/linux/man-pages/man2/prctl.2.html)

### 三、systemd.unit

名称

systemd.unit — 单元配置

大纲

```
*`service`*.service`, `*`socket`*.socket`, `*`device`*.device`, `*`mount`*.mount`, `*`automount`*.automount`, `*`swap`*.swap`, `*`target`*.target`, `*`path`*.path`, `*`timer`*.timer`, `*`slice`*.slice`, `*`scope`*.scope
```



系统单元

```
/etc/systemd/system.control/*`
`/run/systemd/system.control/*`
`/run/systemd/transient/*`
`/run/systemd/generator.early/*`
`/etc/systemd/system/*`
`/etc/systemd/systemd.attached/*`
`/run/systemd/system/*`
`/run/systemd/systemd.attached/*`
`/run/systemd/generator/*`
`…`
`/usr/lib/systemd/system/*`
`/run/systemd/generator.late/*
```



#### 用户单元(私有用户单元+全局用户单元)

```
~/.config/systemd/user.control/*`
`$XDG_RUNTIME_DIR/systemd/user.control/*`
`$XDG_RUNTIME_DIR/systemd/transient/*`
`$XDG_RUNTIME_DIR/systemd/generator.early/*`
`~/.config/systemd/user/*`
`/etc/systemd/user/*`
`$XDG_RUNTIME_DIR/systemd/user/*`
`/run/systemd/user/*`
`$XDG_RUNTIME_DIR/systemd/generator/*`
`~/.local/share/systemd/user/*`
`…`
`/usr/lib/systemd/user/*`
`$XDG_RUNTIME_DIR/systemd/generator.late/*
```



#### 描述

单元文件是 ini 风格的纯文本文件。 封装了有关下列对象的信息： 服务(service)、套接字(socket)、设备(device)、挂载点(mount)、自动挂载点(automount)、 启动目标(target)、交换分区或交换文件(swap)、被监视的路径(path)、任务计划(timer)、 资源控制组(slice)、一组外部创建的进程(scope)。参见 [systemd.syntax(5)](https://www.jinbuguo.com/systemd/systemd.syntax.html#) 以了解通用配置语法。

本手册列出了各类单元所共有的配置选项(亦称"配置指令"或"单元属性")， 这些选项位于单元文件的 [Unit] 或 [Install] 小节。

除了通用的 [Unit] 与 [Install] 小节之外， 每种单元还有各自 专属的小节。 详见各种单元的手册： [systemd.service(5)](https://www.jinbuguo.com/systemd/systemd.service.html#), [systemd.socket(5)](https://www.jinbuguo.com/systemd/systemd.socket.html#), [systemd.device(5)](https://www.jinbuguo.com/systemd/systemd.device.html#), [systemd.mount(5)](https://www.jinbuguo.com/systemd/systemd.mount.html#), [systemd.automount(5)](https://www.jinbuguo.com/systemd/systemd.automount.html#), [systemd.swap(5)](https://www.jinbuguo.com/systemd/systemd.swap.html#), [systemd.target(5)](https://www.jinbuguo.com/systemd/systemd.target.html#), [systemd.path(5)](https://www.jinbuguo.com/systemd/systemd.path.html#), [systemd.timer(5)](https://www.jinbuguo.com/systemd/systemd.timer.html#), [systemd.slice(5)](https://www.jinbuguo.com/systemd/systemd.slice.html#), [systemd.scope(5)](https://www.jinbuguo.com/systemd/systemd.scope.html#).

单元文件将会从多个编译时设定的目录中加载， 下一小节将会详细解释。

单元文件可以通过一个"实例名"参数从"模板文件"构造出来(这个过程叫"实例化")。 "模板文件"(也称"模板单元"或"单元模板")是定义一系列同类型单元的基础。 模板文件的名称必须以 "`@`" 结尾(在类型后缀之前)。 通过实例化得到的单元，其完整的单元名称是在模板文件的类型后缀与 "`@`" 之间插入实例名称形成的。在通过实例化得到的单元内部， 可以使用 "`%i`" 以及其他说明符来引用实例参数， 详见后文。

除了手册中列出的选项之外，单元文件还可以包含更多其他选项。 无法识别的选项不会中断单元文件的加载，但是 systemd 会输出一条警告日志。 如果选项或者小节的名字以 `X-` 开头， 那么 systemd 将会完全忽略它。 以 `X-` 开头的小节中的选项没必要再以 `X-` 开头， 因为整个小节都已经被忽略。 应用程序可以利用这个特性在单元文件中包含额外的信息。

如果想要给一个单元赋予别名，那么可以按照需求，在系统单元目录或用户单元目录中， 创建一个软连接(以别名作为文件名)，并将其指向该单元的单元文件。 例如 `systemd-networkd.service` 在安装时就通过 `/usr/lib/systemd/system/dbus-org.freedesktop.network1.service` 软连接创建了 `dbus-org.freedesktop.network1.service` 别名。 此外，还可以直接在单元文件的 [Install] 小节中使用 `Alias=` 创建别名。 注意，单元文件中设置的别名会随着单元的启用(enable)与禁用(disable)而生效和失效， 也就是别名软连接会随着单元的启用(enable)与禁用(disable)而创建与删除。 例如，因为 `reboot.target` 单元文件中含有 `Alias=ctrl-alt-del.target` 的设置，所以启用(enable)此单元之后，按下 CTRL+ALT+DEL 组合键将会导致启动该单元。单元的别名可以用于 **enable**, **disable**, **start**, **stop**, **status**, … 这些命令中，也可以用于 `Wants=`, `Requires=`, `Before=`, `After=`, … 这些依赖关系选项中。 但是务必注意，不可将单元的别名用于 **preset** 命令中。 再次提醒，通过 `Alias=` 设置的别名仅在单元被启用(enable)之后才会生效。

对于例如 `foo.service` 这样的单元文件， 可以同时存在对应的 `foo.service.wants/` 与 `foo.service.requires/` 目录， 其中可以放置许多指向其他单元文件的软连接。 软连接所指向的单元将会被隐含的添加到 `foo.service` 相应的 `Wants=` 与 `Requires=` 依赖中。 这样就可以方便的为单元添加依赖关系，而无需修改单元文件本身。 向 `.wants/` 与 `.requires/` 目录中添加软连接的首选方法是使用 [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#) 的 **enable** 命令， 它会读取单元文件的 [Install] 小节(详见后文)。

对于例如 `foo.service` 这样的单元文件，可以同时存在对应的 `foo.service.d/` 目录， 当解析完主单元文件之后，目录中所有以 "`.conf`" 结尾的文件，都会被按照文件名的字典顺序，依次解析(相当于依次附加到主单元文件的末尾)。 这样就可以方便的修改单元的设置，或者为单元添加额外的设置，而无需修改单元文件本身。 注意，配置片段("`.conf`" 文件)必须包含明确的小节头(例如 "`[Service]`" 之类)。 对于从模板文件实例化而来的单元，会优先读取与此实例对应的 "`.d/`" 目录(例如 "`foo@bar.service.d/`")中的配置片段("`.conf`" 文件)， 然后才会读取与模板对应的 "`.d/`" 目录(例如 "`foo@.service.d/`")中的配置片段("`.conf`" 文件)。 对于名称中包含连字符("`-`")的单元，将会按特定顺序依次在一组(而不是一个)目录中搜索单元配置片段。 例如对于 `foo-bar-baz.service` 单元来说，将会依次在 `foo-.service.d/`, `foo-bar-.service.d/`, `foo-bar-baz.service.d/` 目录下搜索单元配置片段。这个机制可以方便的为一组相关单元(单元名称的前缀都相同)定义共同的单元配置片段， 特别适合应用于 mount, automount, slice 类型的单元， 因为这些单元的命名规则就是基于连字符构建的。 注意，在前缀层次结构的下层目录中的单元配置片段，会覆盖上层目录中的同名文件， 也就是 `foo-bar-.service.d/10-override.conf` 会覆盖(取代) `foo-.service.d/10-override.conf` 文件。

存放配置片段("`.conf`" 文件)的 "`.d/`" 目录， 除了可以放置在 `/etc/systemd/{system,user}` 目录中， 还可以放置在 `/usr/lib/systemd/{system,user}` 与 `/run/systemd/{system,user}` 目录中。 虽然在优先级上，`/etc` 中的配置片段优先级最高、`/run` 中的配置片段优先级居中、 `/usr/lib` 中的配置片段优先级最低。但是这仅对同名配置片段之间的覆盖关系有意义。 因为所有 "`.d/`" 目录中的配置片段，无论其位于哪个目录， 都会被按照文件名的字典顺序，依次覆盖单元文件中的设置(相当于依次附加到主单元文件的末尾)。

注意，虽然 systemd 为明确设置单元之间的依赖关系提供了灵活的方法， 但是我们反对使用这些方法，你应该仅在万不得已的时候才使用它。 我们鼓励你使用基于 D-Bus 或 socket 的启动机制， 以将单元之间的依赖关系隐含化， 从而得到一个更简单也更健壮的系统。

如上所述，单元可以从模板实例化而来。 这样就可以用同一个模板文件衍生出多个单元。 当 systemd 查找单元文件时，会首先查找与单元名称完全吻合的单元文件， 如果没有找到，并且单元名称中包含 "`@`" 字符， 那么 systemd 将会继续查找拥有相同前缀的模板文件， 如果找到，那么将从这个模板文件实例化一个单元来使用。 例如，对于 `getty@tty3.service` 单元来说， 其对应的模板文件是 `getty@.service` (也就是去掉 "`@`" 与后缀名之间的部分)。

可以在模板文件内部 通过 "`%i`" 引用实例字符串(也就是上例中的"tty3")， 详见后面的小节。

如果一个单元文件的大小为零字节或者是指向 `/dev/null` 的软连接， 那么它的所有相关配置都将被忽略。同时，该单元将被标记为 "`masked`" 状态，并且无法被启动。 这样就可以 彻底屏蔽一个单元(即使手动启动也不行)。

单元文件的格式在未来将保持稳定(参见 [Interface Stability Promise](https://www.freedesktop.org/wiki/Software/systemd/InterfaceStabilityPromise))。



#### 单元名称中的字符转义

有时需要将任意字符串(可以包含任意非NUL字符)转化为合法有效的单元名称。 为了达成这个目标，必须对特殊字符进行转义。 一个典型的例子是，为了便于识别，需要将某些单元的名称精确对应到文件系统上的对象。 例如将 `dev-sda.device` 与 `/dev/sda` 精确对应。

转义规则如下：(1)将 "`/`" 替换为 "`-`" ； (2)保持 ASCII字母与数字 不变； (3)保持 "`_`" 不变； (4)仅当 "`.`" 是首字符时将其替换为"\x2e"，否则保持不变； (5)将上述 1~4 之外的所有其他字符替换为C风格的"\x??"转义序列。

对于文件系统路径来说，"/"的转义规则略有不同，具体说来就是： (1)单纯的根目录"/"将被替换为"-"； (2)将其他路径首尾的"/"删除后再将剩余的"/"替换为"-"。 例如 `/foo//bar/baz/` 将被转义为 "`foo-bar-baz`"

只要知道转义对象是否为文件系统路径， 这种转义规则就是完全可逆的。 [systemd-escape(1)](https://www.jinbuguo.com/systemd/systemd-escape.html#) 可以用来转义与还原字符串。使用 **systemd-escape --path** 转义文件系统路径， 使用 **systemd-escape** 转义其他字符串。



#### 自动依赖



##### 隐含依赖

许多依赖关系是根据单元的类型与设置自动隐含创建的。 这些隐含的依赖关系可以让单元文件的内容更加简洁清爽。 对于各类单元的隐含依赖关系， 可以参考对应手册页的"隐含依赖"小节。

例如，带有 `Type=dbus` 的 service 单元 将会自动隐含 `Requires=dbus.socket` 与 `After=dbus.socket` 依赖。详见 [systemd.service(5)](https://www.jinbuguo.com/systemd/systemd.service.html#) 手册。



##### 默认依赖

默认依赖与隐含依赖类似，不同之处在于默认依赖可以使用 `DefaultDependencies=` 选项进行开关(默认值 `yes` 表示开启默认依赖，而设为 `no` 则表示关闭默认依赖)， 而隐含依赖永远有效。 对于各类单元的默认依赖关系，可以参考对应手册页的"默认依赖"小节。

例如，除非明确设置了 `DefaultDependencies=no` ，否则 target 单元将会默认添加对通过 `Wants=` 或 `Requires=` 汇聚的单元 的 `After=` 依赖。 详见 [systemd.target(5)](https://www.jinbuguo.com/systemd/systemd.target.html#) 手册。注意，可以通过设置 `DefaultDependencies=no` 来关闭默认行为。



#### 单元目录(单元文件加载路径)

systemd 将会从一组在编译时设定好的"单元目录"中加载单元文件(详见下面的两个表格)， 并且较先列出的目录拥有较高的优先级(细节见后文)。 也就是说，高优先级目录中的文件， 将会覆盖低优先级目录中的同名文件。

如果设置了 `$SYSTEMD_UNIT_PATH` 环境变量， 那么它将会取代预设的单元目录。 如果 `$SYSTEMD_UNIT_PATH` 以 "`:`" 结尾， 那么预设的单元目录将会被添加到该变量值的末尾。



**表 1. 当 systemd 以系统实例(`--system`)运行时，加载单元的先后顺序(较前的目录优先级较高)：**

| 系统单元目录                    | 描述                                                         |
| ------------------------------- | ------------------------------------------------------------ |
| `/etc/systemd/system.control`   | 通过 dbus API 创建的永久系统单元                             |
| `/run/systemd/system.control`   | 通过 dbus API 创建的临时系统单元                             |
| `/run/systemd/transient`        | 动态配置的临时单元(系统与全局用户共用)                       |
| `/run/systemd/generator.early`  | 生成的高优先级单元(系统与全局用户共用)(参见 [systemd.generator(7)](https://www.jinbuguo.com/systemd/systemd.generator.html#) 手册中对 *`early-dir`* 的说明) |
| `/etc/systemd/system`           | 本地配置的系统单元                                           |
| `/run/systemd/system`           | 运行时配置的系统单元                                         |
| `/run/systemd/generator`        | 生成的中优先级系统单元(参见 [systemd.generator(7)](https://www.jinbuguo.com/systemd/systemd.generator.html#) 手册中对 *`normal-dir`* 的说明) |
| `/usr/local/lib/systemd/system` | 本地软件包安装的系统单元                                     |
| `/usr/lib/systemd/system`       | 发行版软件包安装的系统单元                                   |
| `/run/systemd/generator.late`   | 生成的低优先级系统单元(参见 [systemd.generator(7)](https://www.jinbuguo.com/systemd/systemd.generator.html#) 手册中对 *`late-dir`* 的说明) |





**表 2. 当 systemd 以用户实例(`--user`)运行时，加载单元的先后顺序(较前的目录优先级较高)：**

| 用户单元目录                                                 | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `$XDG_CONFIG_HOME/systemd/user.control` 或 `~/.config/systemd/user.control` | 通过 dbus API 创建的永久私有用户单元(仅在未设置 `$XDG_CONFIG_HOME` 时才使用 `~/.config` 来替代) |
| `$XDG_RUNTIME_DIR/systemd/user.control`                      | 通过 dbus API 创建的临时私有用户单元                         |
| `/run/systemd/transient`                                     | 动态配置的临时单元(系统与全局用户共用)                       |
| `/run/systemd/generator.early`                               | 生成的高优先级单元(系统与全局用户共用)(参见 [systemd.generator(7)](https://www.jinbuguo.com/systemd/systemd.generator.html#) 手册中对 *`early-dir`* 的说明) |
| `$XDG_CONFIG_HOME/systemd/user` 或 `$HOME/.config/systemd/user` | 用户配置的私有用户单元(仅在未设置 `$XDG_CONFIG_HOME` 时才使用 `~/.config` 来替代) |
| `/etc/systemd/user`                                          | 本地配置的全局用户单元                                       |
| `$XDG_RUNTIME_DIR/systemd/user`                              | 运行时配置的私有用户单元(仅当 $XDG_RUNTIME_DIR 已被设置时有效) |
| `/run/systemd/user`                                          | 运行时配置的全局用户单元                                     |
| `$XDG_RUNTIME_DIR/systemd/generator`                         | 生成的中优先级私有用户单元(参见 [systemd.generator(7)](https://www.jinbuguo.com/systemd/systemd.generator.html#) 手册中对 *`normal-dir`* 的说明) |
| `$XDG_DATA_HOME/systemd/user` 或 `$HOME/.local/share/systemd/user` | 软件包安装在用户家目录中的私有用户单元(仅在未设置 `$XDG_DATA_HOME` 时才使用 `~/.local/share` 来替代) |
| `$dir/systemd/user`(对应 `$XDG_DATA_DIRS` 中的每一个目录(`$dir`)) | 额外安装的全局用户单元，对应 `$XDG_DATA_DIRS`(默认值="/usr/local/share/:/usr/share/") 中的每一个目录。 |
| `/usr/local/lib/systemd/user`                                | 本地软件包安装的全局用户单元                                 |
| `/usr/lib/systemd/user`                                      | 发行版软件包安装的全局用户单元                               |
| `$XDG_RUNTIME_DIR/systemd/generator.late`                    | 生成的低优先级私有用户单元(参见 [systemd.generator(7)](https://www.jinbuguo.com/systemd/systemd.generator.html#) 手册中对 *`late-dir`* 的说明) |



可以使用环境变量来 扩充或更改 systemd 用户实例(`--user`)的单元文件加载路径。 环境变量可以通过环境变量生成器(详见 [systemd.environment-generator(7)](https://www.jinbuguo.com/systemd/systemd.environment-generator.html#) 手册)来设置。特别地， `$XDG_DATA_HOME` 与 `$XDG_DATA_DIRS` 可以方便的通过 [systemd-environment-d-generator(8)](https://www.jinbuguo.com/systemd/systemd-environment-d-generator.html#) 来设置。这样，上表中列出的单元目录正好就是默认值。 要查看实际使用的、基于编译选项与当前环境变量的单元目录列表，可以使用

```
systemd-analyze --user unit-paths
```



此外，还可以通过 [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#) 的 **link** 命令 向上述单元目录中添加额外的单元(不在上述常规单元目录中的单元)。



#### 单元垃圾回收

systemd 会在首次引用一个单元时自动加载该单元的配置， 并在不再需要该单元时自动卸载该单元的配置与状态(垃圾回收)。 可以通过多种不同机制引用单元：

1. 该单元是另外一个已加载单元的依赖，例如 `After=`, `Wants=`, …
2. 该单元正在启动(starting)、运行(running)、重新加载配置(reloading)、停止(stopping)
3. 该单元正处于失败(`failed`)状态(详见下文)
4. 该单元的一个任务正在排队等候执行
5. 该单元正在被一个活动的IPC客户端程序锁定
6. 该单元是一个特殊的"永久"单元，总是被加载并启动。 例如，根文件系统挂载点 `-.mount` 单元、以及 systemd(PID=1) 自身所在的 `init.scope` 单元。
7. 该单元拥有与其关联的、正在运行中的进程

可以使用 `CollectMode=` 选项设置垃圾回收策略， 也就是，是否允许自动卸载处于失败(`failed`)状态的单元 (详见下文)。

当一个单元的配置与状态被卸载之后，该单元的所有执行结果，除了已经记录在日志中的信息之外，所有其他信息， 例如，退出码、退出信号、资源占用，等等，都会消失。

即使单元的配置已经加载，也可以使用 **systemctl daemon-reload** 或其他等效命令，强制重新加载单元配置。 所有已经加载的配置都将被清空， 并被新加载的配置取代(当然，新配置未必就立即生效)， 同时所有运行时状态都会被保存并恢复。



#### [Unit] 小节选项

单元文件中的 [Unit] 小节 包含与单元类型无关的通用信息。 可用的选项(亦称"指令"或"属性")如下：

- `Description=`

  有利于人类阅读的、对单元进行简单描述的字符串。将被 **systemd** 或其他程序用来标记此单元， 这个字符串应该只用于识别此单元即可，不需要过分说明。例如 "`Apache2 Web Server`" 就是一个好例子，而 "`high-performance light-weight HTTP server`" (太通用) 与 "`Apache2`" (信息太少) 则是两个坏例子。因为 **systemd** 将会把这个字符串用于状态信息中("`Starting *`description`*...`", "`Started *`description`*.`", "`Reached target *`description`*.`", "`Failed to start *`description`*.`")，所以这个字符串应该表现的像一个名词， 而不是一个完整的句子或带有动词的短语。比如 "`exiting the container`" 或 "`updating the database once per day.`" 就是典型的坏例子。

- `Documentation=`

  一组用空格分隔的文档URI列表， 这些文档是对此单元的详细说明。 可接受 "`http://`", "`https://`", "`file:`", "`info:`", "`man:`" 五种URI类型。 有关URI语法的详细说明，参见 [uri(7)](http://man7.org/linux/man-pages/man7/uri.7.html) 手册。 这些URI应该按照相关性由高到低列出。 比如，将解释该单元作用的文档放在第一个， 最好再紧跟单元的配置说明， 最后再附上其他文档。 可以多次使用此选项， 依次向文档列表尾部添加新文档。 但是，如果为此选项设置一个空字符串， 那么表示 清空先前已存在的列表。

- `Requires=`

  设置此单元所必须依赖的其他单元。当启动此单元时，也必须启动这里列出的所有其他单元。 如果此处列出的某个单元启动失败、并且恰好又设置了到这个失败单元的 `After=` 依赖，那么将不会启动此单元。此外，无论是否设置了到被依赖单元的 `After=` 依赖，只要某个被依赖的单元被显式停止，那么该单元也会被连带停止。 想要添加多个单元，可以多次使用此选项，也可以设置一个空格分隔的单元列表。 注意，此选项并不影响单元之间的启动或停止顺序。 要想调整单元之间的启动或停止顺序，请使用 `After=` 或 `Before=` 选项。 例如，在 `foo.service` 中设置了 `Requires=bar.service` ， 但是并未使用 `After=` 或 `Before=` 设定两者的启动顺序， 那么，当需要启动 `foo.service` 的时候，这两个单元会被并行的同时启动。 建议使用 `Wants=` 代替 `Requires=` 来设置单元之间的非致命依赖关系， 从而有助于获得更好的健壮性， 特别是在某些单元启动失败的时候。注意，设置了此依赖并不意味着当本单元处于运行状态时，被依赖的其他单元也必须总是处于运行状态。 例如：(1)失败的条件检查(例如后文的 `ConditionPathExists=`, `ConditionPathIsSymbolicLink=`, …)只会导致被依赖的单元跳过启动，而不会导致被依赖的单元启动失败(也就是进入"failed"状态)。 (2)某些被依赖的单元可能会自己主动停止(例如有的服务进程可能会主动干净的退出、有的设备可能被用户拔出)， 而不会导致本单元自身也跟着一起停止。 要想达到这样的效果，可以同时联合使用 `BindsTo=` 与 `After=` 依赖，这样就可以确保：在被依赖的其他单元没有处于运行状态时， 本单元自身永远不会启动成功(详见后文)。注意， 此种依赖关系也可以在单元文件之外通过向 `.requires/`目录中添加软连接来设置。 详见前文。

- `Requisite=`

  与 `Requires=` 类似。不同之处在于：当此单元启动时，这里列出的依赖单元必须已经全部处于启动成功的状态， 否则，此单元将会立即进入启动失败的状态，并且也不会启动那些尚未成功启动的被依赖单元。 因为 `Requisite=` 不隐含任何顺序依赖(即使两个单元在同一个事务中启动)， 所以，此选项经常与 `After=` 一起使用， 以确保此单元不会在启动时间上早于被依赖的单元。如果 `a.service` 中包含了 `Requisite=b.service` ，那么这个依赖关系将在 `b.service` 的属性列表中显示为 `RequisiteOf=a.service` 。 也就是说，不能直接设置 `RequisiteOf=` 依赖。

- `Wants=`

  此选项是 `Requires=` 的弱化版。 当此单元被启动时， 所有这里列出的其他单元只是尽可能被启动。 但是，即使某些单元不存在或者未能启动成功， 也不会影响此单元的启动。 推荐使用此选项来设置单元之间的依赖关系。注意， 此种依赖关系也可以在单元文件之外通过向 `.wants/` 目录中添加软连接来设置， 详见前文。

- `BindsTo=`

  与 `Requires=` 类似，但是依赖性更强： 如果这里列出的任意一个单元停止运行或者崩溃，那么也会连带导致该单元自身被停止。 这就意味着该单元可能因为 这里列出的任意一个单元的 主动退出、某个设备被拔出、某个挂载点被卸载， 而被强行停止。如果将某个被依赖的单元同时放到 `After=` 与 `BindsTo=` 选项中，那么效果将会更加强烈：被依赖的单元必须严格的先于本单元启动成功之后， 本单元才能开始启动。这就意味着，不但在被依赖的单元意外停止时，该单元必须停止， 而且在被依赖的单元由于条件检查失败(例如后文的 `ConditionPathExists=`, `ConditionPathIsSymbolicLink=`, …)而被跳过时， 该单元也将无法启动。正因为如此，在很多场景下，需要同时使用 `BindsTo=` 与 `After=` 选项。如果 `a.service` 中包含了 `BindsTo=b.service` ，那么这个依赖关系将在 `b.service` 的属性列表中显示为 `BoundBy=a.service` 。 也就是说，不能直接设置 `BoundBy=` 依赖。

- `PartOf=`

  与 `Requires=` 类似， 不同之处在于：仅作用于单元的停止或重启。 其含义是，当停止或重启这里列出的某个单元时， 也会同时停止或重启该单元自身。 注意，这个依赖是单向的， 该单元自身的停止或重启并不影响这里列出的单元。如果 `a.service` 中包含了 `PartOf=b.service` ，那么这个依赖关系将在 `b.service` 的属性列表中显示为 `ConsistsOf=a.service` 。 也就是说，不能直接设置 `ConsistsOf=` 依赖。

- `Conflicts=`

  指定单元之间的冲突关系。 接受一个空格分隔的单元列表，表明该单元不能与列表中的任何单元共存， 也就是说：(1)当此单元启动的时候，列表中的所有单元都将被停止； (2)当列表中的某个单元启动的时候，该单元同样也将被停止。 注意，此选项与 `After=` 和 `Before=` 选项没有任何关系。如果两个相互冲突的单元A与B 需要在同一个事务内作为B启动， 那么这个事务要么会失败(A与B都是事务中的必要部分[Requires])， 要么就是必须被修改(A与B中至少有一个是事务中的非必要部分)。 在后一种情况下， 将会剔除一个非必要的单元 (若两个都是非必要的单元， 则优先剔除A)。

- `Before=`, `After=`

  强制指定单元之间的先后顺序，接受一个空格分隔的单元列表。 假定 `foo.service` 单元包含 `Before=bar.service` 设置， 那么当两个单元都需要启动的时候， `bar.service` 将会一直延迟到 `foo.service` 启动完毕之后再启动。 注意，停止顺序与启动顺序正好相反，也就是说， 只有当 `bar.service` 完全停止后，才会停止 `foo.service` 单元。 `After=` 的含义与 `Before=` 正好相反。 假定 `foo.service` 单元包含 `After=bar.service` 设置， 那么当两个单元都需要启动的时候， `foo.service` 将会一直延迟到 `bar.service` 启动完毕之后再启动。 注意，停止顺序与启动顺序正好相反，也就是说， 只有当 `foo.service` 完全停止后，才会停止 `bar.service` 单元。 注意，此二选项仅用于指定先后顺序， 而与 `Requires=`, `Wants=`, `BindsTo=` 这些选项没有任何关系。 不过在实践中也经常遇见将某个单元同时设置到 `After=` 与 `Requires=` 选项中的情形。 可以多次使用此二选项，以将多个单元添加到列表中。 假定两个单元之间存在先后顺序(无论谁先谁后)，并且一个要停止而另一个要启动，那么永远是"先停止后启动"的顺序。 但如果两个单元之间没有先后顺序，那么它们的停止和启动就都是相互独立的，并且是并行的。 对于不同类型的单元来说，判断启动是否已经完成的标准并不完全相同。 特别的，对于设置在 `Before=`/`After=` 中的服务单元来说， 只有在服务单元内配置的所有启动命令全部都已经被调用，并且对于每一个被调用的命令， 要么确认已经调用失败、要么确认已经成功运行的情况下， 才能认为已经完成启动。

- `OnFailure=`

  接受一个空格分隔的单元列表。 当该单元进入失败("`failed`")状态时， 将会启动列表中的单元。使用了 `Restart=` 的服务单元仅在超出启动频率限制之后， 才会进入失败(failed)状态。

- `PropagatesReloadTo=`, `ReloadPropagatedFrom=`

  接受一个空格分隔的单元列表。 `PropagatesReloadTo=` 表示 在 reload 该单元时， 也同时 reload 所有列表中的单元。 `ReloadPropagatedFrom=` 表示 在 reload 列表中的某个单元时， 也同时 reload 该单元。

- `JoinsNamespaceOf=`

  接受一个空格分隔的单元列表， 表示将该单元所启动的进程加入到列表单元的网络及 临时文件(`/tmp`, `/var/tmp`)的名字空间中。 此选项仅适用于支持 `PrivateNetwork=` 与/或 `PrivateTmp=` 指令的单元(对加入者与被加入者都适用)。详见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 手册。 如果单元列表中 仅有一个单元处于已启动状态， 那么该单元将加入到 这个唯一已启动单元的名字空间中。 如果单元列表中 有多个单元处于已启动状态， 那么该单元将 随机加入一个已启动单元的 名字空间中。

- `RequiresMountsFor=`

  接受一个空格分隔的绝对路径列表，表示该单元将会使用到这些文件系统路径。 所有这些路径中涉及的挂载点所对应的 mount 单元，都会被隐式的添加到 `Requires=` 与 `After=` 选项中。 也就是说，这些路径中所涉及的挂载点都会在启动该单元之前被自动挂载。注意，虽然带有 `noauto` 标记的挂载点不会被 `local-fs.target` 自动挂载， 但是它并不影响此选项所设置的依赖关系。 也就是说，带有 `noauto` 标记的挂载点 依然会在启动该单元之前被自动挂载。

- `OnFailureJobMode=`

  可设为 "`fail`", "`replace`", "`replace-irreversibly`", "`isolate`", "`flush`", "`ignore-dependencies`", "`ignore-requirements`" 之一。 默认值是 "`replace`" 。 指定 `OnFailure=` 中列出的单元应该以何种方式排队。值的含义参见 [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#) 手册中对 `--job-mode=` 选项的说明。 如果设为 "`isolate`" ， 那么只能在 `OnFailure=` 中设置一个单独的单元。

- `IgnoreOnIsolate=`

  接受一个布尔值。设为 `yes` 表示在执行 **systemctl isolate ...** 命令时，此单元不会被停止。 对于 service, target, socket, timer, path 单元来说，默认值是 `false` ； 对于 slice, scope, device, swap, mount, automount 单元来说， 默认值是 `true` 。

- `StopWhenUnneeded=`

  如果设为 `yes` ， 那么当此单元不再被任何已启动的单元依赖时， 将会被自动停止。 默认值 `no` 的含义是， 除非此单元与其他即将启动的单元冲突， 否则即使此单元已不再被任何已启动的单元依赖， 也不会自动停止它。

- `RefuseManualStart=`, `RefuseManualStop=`

  如果设为 `yes` ， 那么此单元将拒绝被手动启动(`RefuseManualStart=`) 或拒绝被手动停止(`RefuseManualStop=`)。 也就是说， 此单元只能作为其他单元的依赖条件而存在， 只能因为依赖关系而被间接启动或者间接停止， 不能由用户以手动方式直接启动或者直接停止。 设置此选项是为了 禁止用户意外的启动或者停止某些特定的单元。 默认值是 `no`

- `AllowIsolate=`

  如果设为 `yes` ， 那么此单元将允许被 **systemctl isolate** 命令操作， 否则将会被拒绝。 唯一一个将此选项设为 `yes` 的理由，大概是为了兼容SysV初始化系统。 此时应该仅考虑对 target 单元进行设置， 以防止系统进入不可用状态。 建议保持默认值 `no`

- `DefaultDependencies=`

  默认值 `yes` 表示为此单元隐式地创建默认依赖。 不同类型的单元，其默认依赖也不同，详见各自的手册页。 例如对于 service 单元来说， 默认的依赖关系是指： (1)开机时，必须在基础系统初始化完成之后才能启动该服务； (2)关机时，必须在该服务完全停止后才能关闭基础系统。 通常，只有那些在系统启动的早期就必须启动的单元， 以及那些必须在系统关闭的末尾才能关闭的单元， 才可以将此选项设为 `no` 。 注意，设为 `no` 并不表示取消所有的默认依赖， 只是表示取消非关键的默认依赖。 强烈建议对绝大多数普通单元 保持此选项的默认值 `yes` 。

- `CollectMode=`

  设置此单元的"垃圾回收"策略。可设为 `inactive`(默认值) 或 `inactive-or-failed` 之一。默认值 `inactive` 表示如果该单元处于停止(`inactive`)状态，并且没有被其他客户端、任务、单元所引用，那么该单元将会被卸载。 注意，如果此单元处于失败(`failed`)状态，那么是不会被卸载的， 它会一直保持未卸载状态，直到用户调用 **systemctl reset-failed** (或类似的命令)重置了 `failed` 状态。设为 `inactive-or-failed` 表示无论此单元处于停止(`inactive`)状态还是失败(`failed`)状态， 都将被卸载(无需重置 `failed` 状态)。 注意，在这种"垃圾回收"策略下， 此单元的所有结果(退出码、退出信号、资源消耗 …) 都会在此单元结束之后立即清除(只剩下此前已经记录在日志中的痕迹)。

- `FailureAction=`, `SuccessAction=`

  当此单元停止并进入失败(`failed`)或停止(`inactive`)状态时，应当执行什么动作。 对于系统单元，可以设为 `none`, `reboot`, `reboot-force`, `reboot-immediate`, `poweroff`, `poweroff-force`, `poweroff-immediate`, `exit`, `exit-force` 之一。 对于用户单元，仅可设为 `none`, `exit`, `exit-force` 之一。两个选项的默认值都是 `none`默认值 `none` 表示 不触发任何动作。 `reboot`/`poweroff` 表示按照常规关机流程重启/关闭整个系统(等价于 **systemctl reboot|poweroff**)。 `reboot-force`/`poweroff-force` 表示强制杀死所有进程之后强制重启/关机， 虽然可能会造成应用程序数据丢失，但是不会造成文件系统不一致(等价于 **systemctl reboot|poweroff -f**)。 `reboot-immediate`/`poweroff-immediate` 表示强制立即执行 [reboot(2)](http://man7.org/linux/man-pages/man2/reboot.2.html) 系统调用重启/关机， 可能会造成数据丢失以及文件系统不一致(等价于 **systemctl reboot|poweroff -ff**)。 `exit` 表示按照常规关闭流程，按部就班的退出 systemd 系统管理器。 `exit-force` 表示立即强制退出 systemd 系统管理器(不再按部就班的逐一退出全部服务)。 当设为 `exit` 或 `exit-force` 时， systemd 系统管理器将会默认把此单元主进程的返回值(如果有)用作系统管理器自身的返回值。 当然，这个默认行为可以通过下面的 `FailureActionExitStatus=`/`SuccessActionExitStatus=` 进行修改。

- `FailureActionExitStatus=`, `SuccessActionExitStatus=`

  当 `FailureAction=`/`SuccessAction=` 的值为 `exit` 或 `exit-force` 之一，并且设定的动作被触发时，应该返回什么样退出码给容器管理器(对于系统服务) 或 systemd 系统管理器(对于用户服务)。 默认情况下，将会使用该单元主进程的退出码(如果有)。 取值范围是 0…255 之间的一个整数。 设为空字符串表示重置回默认行为。

- `JobTimeoutSec=`, `JobRunningTimeoutSec=`

  当该单元的一个任务(job)进入队列的时候， `JobTimeoutSec=` 用于设置从该任务进入队列开始计时、到该任务最终完成，最多可以使用多长时间， `JobRunningTimeoutSec=` 用于设置从该任务实际运行开始计时、到该任务最终完成，最多可以使用多长时间。 如果上述任意一个设置超时，那么超时的任务将被撤销，并且该单元将保持其现有状态不变(而不是进入 "`failed`" 状态)。 对于非 device 单元来说，`DefaultTimeoutStartSec=` 选项的默认值是 "`infinity`"(永不超时)， 而 `JobRunningTimeoutSec=` 的默认值等于 `DefaultTimeoutStartSec=` 的值。 注意，此处设置的超时不是指单元自身的超时(例如 `TimeoutStartSec=` 就是指单元自身的超时)， 而是指该单元在启动或者停止等状态变化过程中，等候某个外部任务完成的最长时限。 换句话说，适用于单元自身的超时设置(例如 `TimeoutStartSec=`)用于指定单元自身在改变其状态时，总共允许使用多长时间； 而此处设置的超时则是设置此单元在改变其状态的过程中，等候某个外部任务完成所能容忍的最长时间。

- `JobTimeoutAction=`, `JobTimeoutRebootArgument=`

  `JobTimeoutAction=` 用于指定当超时发生时(参见上文的 `JobTimeoutSec=` 与 `JobRunningTimeoutSec=` 选项)，将触发什么样的额外动作。 可接受的值与 `StartLimitAction=` 相同，默认值为 `none` 。 `JobTimeoutRebootArgument=` 用于指定传递给 [reboot(2)](http://man7.org/linux/man-pages/man2/reboot.2.html) 系统调用的字符串参数。

- `StartLimitIntervalSec=*`interval`*`, `StartLimitBurst=*`burst`*`

  设置单元的启动频率限制。 也就是该单元在 *`interval`* 时间内最多允许启动 *`burst`* 次。 `StartLimitIntervalSec=` 用于设置时长(默认值等于 systemd 配置文件(system.conf)中 `DefaultStartLimitIntervalSec=` 的值)，设为 0 表示没有限制。 `StartLimitBurst=` 用于设置在给定的时长内，最多允许启动多少次(默认值等于 systemd 配置文件(system.conf)中 `DefaultStartLimitBurst=` 的值)。 虽然此选项通常与 `Restart=` 选项(参见 [systemd.service(5)](https://www.jinbuguo.com/systemd/systemd.service.html#)) 一起使用， 但实际上，此选项作用于任何方式的启动(包括手动启动)，而不仅仅是由 `Restart=` 触发的启动。 注意，一旦某个设置了 `Restart=` 自动重启逻辑的单元触碰到了启动频率限制， 那么该单元将再也不会尝试自动重启； 不过，如果该单元在经过 *`interval`* 时长之后，又被手动重启成功的话，那么该单元的自动重启逻辑将会被再次激活。 注意，**systemctl reset-failed** 命令能够重置单元的启动频率计数器。 系统管理员在手动启动某个已经触碰到了启动频率限制的单元之前，可以使用这个命令清除启动限制。 注意，因为启动频率限制位于所有单元条件检查之后， 所以基于失败条件的启动不会计入启动频率限制的启动次数之中。 注意，这些选项对 slice, target, device, scope 单元没有意义， 因为这几种单元要么永远不会启动失败、要么只能成功启动一次。当一个单元因为垃圾回收(见前文)而被卸载的时候， 该单元的启动频率计数器也会被一起清除。 这就意味着对不被持续引用的单元设置启动频率限制是无效的。

- `StartLimitAction=`

  设置该单元在触碰了 `StartLimitIntervalSec=` 与 `StartLimitBurst=` 定义的启动频率限制时，将会执行什么动作。 可接受的值与 `FailureAction=`/`SuccessAction=` 相同，值的含义也相同。 默认值 `none` 表示除了禁止启动之外， 不触发任何其他动作。

- `RebootArgument=`

  当 `StartLimitAction=` 或 `FailureAction=` 触发重启动作时， 此选项的值就是传递给 [reboot(2)](http://man7.org/linux/man-pages/man2/reboot.2.html) 系统调用的字符串参数。 相当于 **systemctl reboot** 命令接收的可选参数。

- `ConditionArchitecture=`, `ConditionVirtualization=`, `ConditionHost=`, `ConditionKernelCommandLine=`, `ConditionKernelVersion=`, `ConditionSecurity=`, `ConditionCapability=`, `ConditionACPower=`, `ConditionNeedsUpdate=`, `ConditionFirstBoot=`, `ConditionPathExists=`, `ConditionPathExistsGlob=`, `ConditionPathIsDirectory=`, `ConditionPathIsSymbolicLink=`, `ConditionPathIsMountPoint=`, `ConditionPathIsReadWrite=`, `ConditionDirectoryNotEmpty=`, `ConditionFileNotEmpty=`, `ConditionFileIsExecutable=`, `ConditionUser=`, `ConditionGroup=`, `ConditionControlGroupController=`

  这组选项用于在启动单元之前，首先测试特定的条件是否为真。 若为假，则悄无声息地跳过此单元的启动(仅是跳过，而不是进入"`failed`"状态)。 注意，即使某单元由于测试条件为假而被跳过， 那些由于依赖关系而必须先于此单元启动的单元并不会受到影响(也就是会照常启动)。 可以使用条件表达式来跳过那些对于本机系统无用的单元， 比如那些对于本机内核或运行环境没有用处的功能。 如果想要单元在测试条件为假时， 除了跳过启动之外，还要在日志中留下痕迹(而不是悄无声息的跳过)， 可以使用对应的另一组 `AssertArchitecture=`, `AssertVirtualization=`, … 选项(见后文)。`ConditionArchitecture=` 检测是否运行于 特定的硬件平台： `x86`, `x86-64`, `ppc`, `ppc-le`, `ppc64`, `ppc64-le`, `ia64`, `parisc`, `parisc64`, `s390`, `s390x`, `sparc`, `sparc64`, `mips`, `mips-le`, `mips64`, `mips64-le`, `alpha`, `arm`, `arm-be`, `arm64`, `arm64-be`, `sh`, `sh64`, `m68k`, `tilegx`, `cris`, `arc`, `arc-be`, `native`(编译 systemd 时的目标平台)。 可以在这些关键字前面加上感叹号(!)前缀 表示逻辑反转。注意， `Personality=` 的值 对此选项 没有任何影响。`ConditionVirtualization=` 检测是否运行于(特定的)虚拟环境中： `yes`(某种虚拟环境), `no`(物理机), `vm`(某种虚拟机), `container`(某种容器), `qemu`, `kvm`, `zvm`, `vmware`, `microsoft`, `oracle`, `xen`, `bochs`, `uml`, `bhyve`, `qnx`, `openvz`, `lxc`, `lxc-libvirt`, `systemd-nspawn`, `docker`, `rkt`, `private-users`(用户名字空间)。参见 [systemd-detect-virt(1)](https://www.jinbuguo.com/systemd/systemd-detect-virt.html#) 手册以了解所有已知的虚拟化技术及其标识符。 如果嵌套在多个虚拟化环境内， 那么以最内层的那个为准。 可以在这些关键字前面加上感叹号(!)前缀表示逻辑反转。`ConditionHost=` 检测系统的 hostname 或者 "machine ID" 。 参数可以是：(1)一个主机名字符串(可以使用 shell 风格的通配符)， 该字符串将会与 本机的主机名(也就是 [gethostname(2)](http://man7.org/linux/man-pages/man2/gethostname.2.html) 的返回值)进行匹配；(2)或者是一个 "machine ID" 格式的字符串(参见 [machine-id(5)](https://www.jinbuguo.com/systemd/machine-id.html#) 手册)。 可以在字符串前面加上感叹号(!)前缀表示逻辑反转。`ConditionKernelCommandLine=` 检测是否设置了某个特定的内核引导选项。 参数可以是一个单独的单词，也可以是一个 "`var=val`" 格式的赋值字符串。 如果参数是一个单独的单词，那么以下两种情况都算是检测成功： (1)恰好存在一个完全匹配的单词选项； (2)在某个 "`var=val`" 格式的内核引导选项中等号前的 "`var`" 恰好与该单词完全匹配。 如果参数是一个 "`var=val`" 格式的赋值字符串， 那么必须恰好存在一个完全匹配的 "`var=val`" 格式的内核引导选项，才算检测成功。 可以在字符串前面加上感叹号(!)前缀表示逻辑反转。`ConditionKernelVersion=` 检测内核版本(**uname -r**) 是否匹配给定的表达式(或在字符串前面加上感叹号(!)前缀表示"不匹配")。 表达式必须是一个单独的字符串。如果表达式以 "`<`", "`<=`", "`=`", "`>=`", "`>`" 之一开头， 那么表示对内核版本号进行比较，否则表示按照 shell 风格的通配符表达式进行匹配。注意，企图根据内核版本来判断内核支持哪些特性是不可靠的。 因为发行版厂商经常将高版本内核的新驱动和新功能移植到当前发行版使用的低版本内核中， 所以，对内核版本的检查是不能在不同发行版之间随意移植的， 不应该用于需要跨发行版部署的单元。`ConditionSecurity=` 检测是否启用了 特定的安全技术： `selinux`, `apparmor`, `tomoyo`, `ima`, `smack`, `audit`, `uefi-secureboot` 。 可以在这些关键字前面加上感叹号(!)前缀表示逻辑反转。`ConditionCapability=` 检测 systemd 的 capability 集合中 是否存在 特定的 [capabilities(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html) 。 参数应设为例如 "`CAP_MKNOD`" 这样的 capability 名称。 注意，此选项不是检测特定的 capability 是否实际可用，而是仅检测特定的 capability 在绑定集合中是否存在。 可以在名称前面加上感叹号(!)前缀表示逻辑反转。`ConditionACPower=` 检测系统是否 正在使用交流电源。 `yes` 表示至少在使用一个交流电源， 或者更本不存在任何交流电源。 `no` 表示存在交流电源， 但是 没有使用其中的任何一个。`ConditionNeedsUpdate=` 可设为 `/var` 或 `/etc` 之一， 用于检测指定的目录是否需要更新。 设为 `/var` 表示 检测 `/usr` 目录的最后更新时间(mtime) 是否比 `/var/.updated` 文件的最后更新时间(mtime)更晚。 设为 `/etc` 表示 检测 `/usr` 目录的最后更新时间(mtime) 是否比 `/etc/.updated` 文件的最后更新时间(mtime)更晚。 可以在值前面加上感叹号(!)前缀表示逻辑反转。 当更新了 `/usr` 中的资源之后，可以通过使用此选项， 实现在下一次启动时更新 `/etc` 或 `/var` 目录的目的。 使用此选项的单元必须设置 `ConditionFirstBoot=systemd-update-done.service` ， 以确保在 `.updated` 文件被更新之前启动完毕。 参见 [systemd-update-done.service(8)](https://www.jinbuguo.com/systemd/systemd-update-done.service.html#) 手册。`ConditionFirstBoot=` 可设为 `yes` 或 `no` 。 用于检测 `/etc` 目录是否处于未初始化的原始状态(重点是 `/etc/machine-id` 文件是否存在)。 此选项可用于系统出厂后(或者恢复出厂设置之后)， 首次开机时执行必要的初始化操作。`ConditionPathExists=` 检测 指定的路径 是否存在， 必须使用绝对路径。 可以在路径前面 加上感叹号(!)前缀 表示逻辑反转。`ConditionPathExistsGlob=` 与 `ConditionPathExists=` 类似， 唯一的不同是支持 shell 通配符。`ConditionPathIsDirectory=` 检测指定的路径是否存在并且是一个目录，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀表示逻辑反转。`ConditionPathIsSymbolicLink=` 检测指定的路径是否存在并且是一个软连接，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀 表示逻辑反转。`ConditionPathIsMountPoint=` 检测指定的路径是否存在并且是一个挂载点，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀表示逻辑反转。`ConditionPathIsReadWrite=` 检测指定的路径是否存在并且可读写(rw)，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀 表示逻辑反转。`ConditionDirectoryNotEmpty=` 检测指定的路径是否存在并且是一个非空的目录，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀 表示逻辑反转。`ConditionFileNotEmpty=` 检测指定的路径是否存在并且是一个非空的普通文件，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀 表示逻辑反转。`ConditionFileIsExecutable=` 检测指定的路径是否存在并且是一个可执行文件，必须使用绝对路径。 可以在路径前面加上感叹号(!)前缀 表示逻辑反转。`ConditionUser=` 检测 systemd 是否以给定的用户身份运行。 参数可以是数字形式的 "`UID`" 、 或者字符串形式的UNIX用户名、 或者特殊值 "`@system`"(表示属于系统用户范围内) 。 此选项对于系统服务无效， 因为管理系统服务的 systemd 进程 总是以 root 用户身份运行。`ConditionGroup=` 检测 systemd 是否以给定的用户组身份运行。 参数可以是数字形式的 "`GID`" 或者字符串形式的UNIX组名。 注意：(1)这里所说的"组"可以是"主组"(Primary Group)、"有效组"(Effective Group)、"辅助组"(Auxiliary Group)； (2)此选项不存在特殊值 "`@system`"`ConditionControlGroupController=` 检测给定的一组 cgroup 控制器(例如 `cpu`)是否全部可用。 通过例如 `cgroup_disable=controller` 这样的内核命令行可以禁用名为"controller"的 cgroup 控制器。 列表中的多个 cgroup 控制器之间可以使用空格分隔。 不能识别的 cgroup 控制器将被忽略。 能够识别的全部 cgroup 控制器如下： `cpu`, `cpuacct`, `io`, `blkio`, `memory`, `devices`, `pids`如果在条件之前加上管道符(|)，那么这个条件就是"触发条件"， 其含义是只要满足一个触发条件，该单元就会被启动； 如果在条件之前没有管道符(|)，那么这个条件就是"普通条件"， 其含义是必须满足全部普通条件，该单元才会被启动。 如果在某个单元文件内， 同时存在"触发条件"与"普通条件"，那么必须满足全部普通条件， 并且至少满足一个触发条件，该单元才会被启动。 如果需要对某个条件同时使用"|"与"!"， 那么"|"必须位于"!"之前。 除 `ConditionPathIsSymbolicLink=` 之外， 其他路径检测选项都会追踪软连接。 如果将上述某个检测选项设为空字符串， 那么表示重置该选项先前的所有设置， 也就是清空该选项先前的设置。

- `AssertArchitecture=`, `AssertVirtualization=`, `AssertHost=`, `AssertKernelCommandLine=`, `AssertKernelVersion=`, `AssertSecurity=`, `AssertCapability=`, `AssertACPower=`, `AssertNeedsUpdate=`, `AssertFirstBoot=`, `AssertPathExists=`, `AssertPathExistsGlob=`, `AssertPathIsDirectory=`, `AssertPathIsSymbolicLink=`, `AssertPathIsMountPoint=`, `AssertPathIsReadWrite=`, `AssertDirectoryNotEmpty=`, `AssertFileNotEmpty=`, `AssertFileIsExecutable=`, `AssertUser=`, `AssertGroup=`, `AssertControlGroupController=`

  与前一组 `ConditionArchitecture=`, `ConditionVirtualization=`, … 测试选项类似，这一组选项用于在单元启动之前， 首先进行相应的断言检查。不同之处在于，任意一个断言的失败， 都会导致跳过该单元的启动并将失败的断言突出记录在日志中。 注意，断言失败并不导致该单元进入失败("`failed`")状态(实际上，该单元的状态不会发生任何变化)， 它仅影响该单元的启动任务队列。 如果用户希望清晰的看到某些单元因为未能满足特定的条件而导致没有正常启动， 那么可以使用断言表达式。注意，无论是前一组条件表达式、还是这一组断言表达式，都不会改变单元的状态。 因为这两组表达式都是在启动任务队列开始执行时进行检查(也就是，位于依赖任务队列之后、该单元自身启动任务队列之前)， 所以，条件表达式和断言表达式 都不适合用于对单元的依赖条件进行检查。

- `SourcePath=`

  指定 生成此单元时所参考的配置文件。 仅用于单元生成器 标识此单元生成自何处。 普通的单元 不应该使用它。



#### 单元属性的正反对应

那些与其他单元关联的属性 通常同时显示(**systemctl show**)在两个关联单元的属性中。 多数情况下， 属性的名称就是单元配置选项的名称，但并不总是如此。 下表展示了存在依赖关系的两个单元的属性是如何显示的， 同时也展示了"源"单元的属性与"目标"单元的属性之间的对应关系。



**表 3. "正向"与"反向"单元属性**

| "正向"属性              | "反向"属性              | 用于何处                     |
| ----------------------- | ----------------------- | ---------------------------- |
| `Before=`               | `After=`                | [Unit] 小节                  |
| `After=`                | `Before=`               |                              |
| `Requires=`             | `RequiredBy=`           | [Unit] 小节； [Install] 小节 |
| `Wants=`                | `WantedBy=`             | [Unit] 小节； [Install] 小节 |
| `PartOf=`               | `ConsistsOf=`           | [Unit] 小节； 自动生成       |
| `BindsTo=`              | `BoundBy=`              | [Unit] 小节； 自动生成       |
| `Requisite=`            | `RequisiteOf=`          | [Unit] 小节； 自动生成       |
| `Triggers=`             | `TriggeredBy=`          | 自动生成(参见下文的解释)     |
| `Conflicts=`            | `ConflictedBy=`         | [Unit] 小节； 自动生成       |
| `PropagatesReloadTo=`   | `ReloadPropagatedFrom=` | [Unit] 小节                  |
| `ReloadPropagatedFrom=` | `PropagatesReloadTo=`   |                              |
| `Following=`            | n/a                     | 自动生成                     |



`WantedBy=` 与 `RequiredBy=` 位于 [Install] 小节，仅用于在 `.wants/` 与 `.requires/` 目录中创建软连接， 不能直接用作单元属性。

`ConsistsOf=`, `BoundBy=`, `RequisiteOf=`, `ConflictedBy=` 只能由对应的"正向"属性自动隐式创建，而不能直接在单元文件中设置。

`Triggers=` 只能隐式的创建于 socket, path, automount 单元之中。 默认触发对应的同名单元，但是可以通过 `Sockets=`, `Service=`, `Unit=` 选项进行改写。详见 [systemd.service(5)](https://www.jinbuguo.com/systemd/systemd.service.html#), [systemd.socket(5)](https://www.jinbuguo.com/systemd/systemd.socket.html#), [systemd.path(5)](https://www.jinbuguo.com/systemd/systemd.path.html#), [systemd.automount(5)](https://www.jinbuguo.com/systemd/systemd.automount.html#) 手册。`TriggeredBy=` 只能隐式的创建于被触发的单元之中。

`Following=` 用于汇聚设备别名， 并指向用于跟踪设备状态的"主"设备单元，通常对应到一个 sysfs 文件系统路径。 它并不会显示在"目标"单元中。



#### [Install] 小节选项

"`[Install]`" 小节包含单元的启用信息。 事实上，[systemd(1)](https://www.jinbuguo.com/systemd/systemd.html#) 在运行时并不使用此小节。 只有 [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#) 的 **enable** 与 **disable** 命令在启用/停用单元时才会使用此小节。 [译者注]"启用"一个单元多数时候在效果上相当于将这个单元设为"开机时自动启动"或"插入某个硬件时自动启动"； "停用"一个单元多数时候在效果上相当于撤销该单元的"开机时自动启动"或"插入某个硬件时自动启动"。

- `Alias=`

  启用时使用的别名，可以设为一个空格分隔的别名列表。 每个别名的后缀(也就是单元类型)都必须与该单元自身的后缀相同。 如果多次使用此选项，那么每个选项所设置的别名都会被添加到别名列表中。 在启用此单元时，**systemctl enable** 命令将会为每个别名创建一个指向该单元文件的软连接。 注意，因为 mount, slice, swap, automount 单元不支持别名， 所以不要在这些类型的单元中使用此选项。

- `WantedBy=`, `RequiredBy=`

  接受一个空格分隔的单元列表， 表示在使用 **systemctl enable** 启用此单元时， 将会在每个列表单元的 `.wants/` 或 `.requires/` 目录中创建一个指向该单元文件的软连接。 这相当于为每个列表中的单元文件添加了 `Wants=此单元` 或 `Requires=此单元` 选项。 这样当列表中的任意一个单元启动时，该单元都会被启动。 有关 `Wants=` 与 `Requires=` 的详细说明， 参见前面 [Unit] 小节的说明。 如果多次使用此选项， 那么每个选项的单元列表都会合并在一起。在普通的 `bar.service` 单元内设置 **WantedBy=foo.service** 选项 与设置 **Alias=foo.service.wants/bar.service** 选项基本上是等价的。 但是对于模板单元来说，情况则有所不同。 虽然必须使用实例名称调用 **systemctl enable** 命令， 但是实际上添加到 `.wants/` 或 `.requires/` 目录中的软连接， 指向的却是模板单元(因为并不存在真正的单元实例文件)。 假设 `getty@.service` 文件中存在 **WantedBy=getty.target** 选项，那么 **systemctl enable getty@tty2.service** 命令将会创建一个 `getty.target.wants/getty@tty2.service` 软连接(指向 `getty@.service`)

- `Also=`

  设置此单元的附属单元， 可以设为一个空格分隔的单元列表。 表示当使用 **systemctl enable** 启用 或 **systemctl disable** 停用 此单元时， 也同时自动的启用或停用附属单元。如果多次使用此选项， 那么每个选项所设置的附属单元列表 都会合并在一起。

- `DefaultInstance=`

  仅对模板单元有意义， 用于指定默认的实例名称。 如果启用此单元时没有指定实例名称， 那么 将使用这里设置的名称。

在 [Install] 小节的选项中，可以使用如下替换符： %n, %N, %p, %i, %j, %g, %G, %U, %u, %m, %H, %b, %v 。 每个符号的具体含义详见下一小节。



#### 替换符

在许多选项中都可以使用一些替换符(不只是 [Install] 小节中的选项)， 以引用一些运行时才能确定的值， 从而可以写出更通用的单元文件。 替换符必须是已知的、并且是可以解析的，这样设置才能生效。 当前可识别的所有替换符及其解释如下：



**表 4. 可以用在单元文件中的替换符**

| 替换符 | 含义                                                         |
| ------ | ------------------------------------------------------------ |
| "`%b`" | 系统的"Boot ID"字符串。参见 [random(4)](http://man7.org/linux/man-pages/man4/random.4.html) 手册 |
| "`%C`" | 缓存根目录。对于系统实例来说是 `/var/cache` ；对于用户实例来说是 "`$XDG_CACHE_HOME`" |
| "`%E`" | 配置根目录。对于系统实例来说是 `/etc` ；对于用户实例来说是 "`$XDG_CONFIG_HOME`" |
| "`%f`" | 原始单元文件名称(不含路径，且遵守前文描述的已转义绝对文件系统路径的还原规则)。对于实例化的单元，就是带有 `/` 前缀的原始实例名；对于其他单元，就是带有 `/` 前缀的原始前缀名。 |
| "`%h`" | 用户的家目录。运行 systemd 实例的用户的家目录，对于系统实例则是 "`/root`" |
| "`%H`" | 系统的主机名(hostname)                                       |
| "`%i`" | 已转义的实例名称。对于实例化单元，就是 "`@`" 和后缀之间的部分。对于非实例化单元则为空。 |
| "`%I`" | 原始实例名称。对于实例化单元，就是 "`@`" 和后缀之间的部分(已还原的)。对于非实例化单元则为空。 |
| "`%j`" | 已转义的前缀名最后一部分。也就是前缀名中最后一个 "`-`" 之后的部分。如果没有 "`-`" 那么与 "`%p`" 相同。 |
| "`%J`" | 原始前缀名最后一部分。也就是前缀名中最后一个 "`-`" 之后的部分(已还原的)。如果没有 "`-`" 那么与 "`%p`" 相同。 |
| "`%L`" | 日志根目录。对于系统实例来说是 `/var/log` ；对于用户实例来说是 "`$XDG_CONFIG_HOME`"`/log` |
| "`%m`" | 系统的"Machine ID"字符串。参见 [machine-id(5)](https://www.jinbuguo.com/systemd/machine-id.html#) 手册 |
| "`%n`" | 带类型后缀的完整单元名称                                     |
| "`%N`" | 无类型后缀的完整单元名称                                     |
| "`%p`" | 已转义的前缀名称。对于实例化单元来说，就是单元名称里第一个 "`@`" 之前的字符串。对于非实例化单元来说，等价于 "`%N`" |
| "`%P`" | 原始前缀名称。对于实例化单元来说，就是单元名称里第一个 "`@`" 之前的字符串(已还原的)。对于非实例化单元来说，等价于 "`%N`" |
| "`%s`" | 用户的shell。运行 systemd 实例的用户的shell，对于系统实例则是 "`/bin/sh`" |
| "`%S`" | 状态根目录。对于系统实例来说是 `/var/lib` ；对于用户实例来说是 "`$XDG_CONFIG_HOME`" |
| "`%t`" | 运行时根目录。对于系统实例来说是 `/run` ；对于用户实例来说是 "`$XDG_RUNTIME_DIR`" |
| "`%T`" | 临时文件目录。也就是 `/tmp` 或 "`$TMPDIR`", "`$TEMP`", "`$TMP`" 之一(若已设置) |
| "`%g`" | 运行 systemd 用户实例的组名称。对于 systemd 系统实例来说，则是 "`root`" |
| "`%G`" | 运行 systemd 用户实例的组GID。对于 systemd 系统实例来说，则是 "`0`" |
| "`%u`" | 运行 systemd 用户实例的用户名称。对于 systemd 系统实例来说，则是 "`root`" |
| "`%U`" | 运行 systemd 用户实例的用户UID。对于 systemd 系统实例来说，则是 "`0`" |
| "`%v`" | 内核版本(**uname -r** 的输出)                                |
| "`%V`" | 存放大体积临时文件以及持久临时文件的目录。也就是 `/var/tmp` 或 "`$TMPDIR`", "`$TEMP`", "`$TMP`" 之一(若已设置) |
| "`%%`" | 百分号自身(%)。使用 "`%%`" 表示一个真正的 "`%`" 字符。       |





#### 例子



**例 1. 允许单元被启用**

下面这个 `foo.service` 单元中的 [Install] 小节表明该单元可以通过 **systemctl enable** 命令启用。

```
[Unit]
Description=Foo

[Service]
ExecStart=/usr/sbin/foo-daemon

[Install]
WantedBy=multi-user.target
```

执行 **systemctl enable** 启用命令之后， 将会建立一个指向该单元文件的软链接 `/etc/systemd/system/multi-user.target.wants/foo.service` ， 表示将 `foo.service` 包含到 `multi-user.target` 目标中， 这样，当启动 `multi-user.target` 目标时， 将会自动起动 `foo.service` 服务。 同时，**systemctl disable** 命令 将会删除这个软连接。





**例 2. 覆盖软件包的默认设置**

以例如 `foo.type` 这样的系统单元为例， 有两种修改单元文件的方法： (1)将单元文件从 `/usr/lib/systemd/system` 目录 复制到 `/etc/systemd/system` 目录中， 然后直接修改复制后的副本。 (2)创建 `/etc/systemd/system/foo.type.d/` 目录， 并在其中创建一些 `*`name`*.conf` 文件， 然后 仅针对性的修改某些个别选项。

第一种方法的优点是易于修改整个单元， 因为原有的单元文件会被完全忽略。 但此种方法的缺点是， 当原有的单元文件被更新时， 变更不能在修改后的副本上自动体现出来。

第二种方法的优点是仅需修改个别选项， 并且原有单元文件的更新能够自动生效。 因为 `.conf` 文件只会按照其文件名的字典顺序，被依次追加到原有单元文件的尾部。 但此种方法的缺点是原有单元文件的更新 有可能导致与 `.conf` 文件中的设置不兼容。

这同样适用于 systemd 用户实例， 只是用户单元文件的文件系统位置不同而已。 参见前文的"单元目录"小节。

下面是一个实例，假定原有的单元文件 `/usr/lib/systemd/system/httpd.service` 包含以下内容：

```
[Unit]
Description=Some HTTP server
After=remote-fs.target sqldb.service
Requires=sqldb.service
AssertPathExists=/srv/webserver

[Service]
Type=notify
ExecStart=/usr/sbin/some-fancy-httpd-server
Nice=5

[Install]
WantedBy=multi-user.target
```

假定系统管理员想要修改几个设置： (1)本地并不存在 `/srv/webserver` 目录，需要修改为 `/srv/www` 目录。 (2)让此服务依赖于本地已经存在的 `memcached.service` 服务(`Requires=`)， 且在其后启动(`After=`)。 (3)为了加固此服务， 添加一个 `PrivateTmp=` 设置(参见 [systemd.exec(5)](https://www.jinbuguo.com/systemd/systemd.exec.html#) 手册)。 (4)将此服务的进程谦让值重置为默认值"0"。

第一种方法，将原有的单元文件复制到 `/etc/systemd/system/httpd.service` 并做相应的修改：

```
[Unit]
Description=Some HTTP server
After=remote-fs.target sqldb.service memcached.service
Requires=sqldb.service memcached.service
AssertPathExists=/srv/www

[Service]
Type=notify
ExecStart=/usr/sbin/some-fancy-httpd-server
Nice=0
PrivateTmp=yes

[Install]
WantedBy=multi-user.target
```

第二种方法， 创建配置片段 `/etc/systemd/system/httpd.service.d/local.conf` 并在其中填入如下内容：

```
[Unit]
After=memcached.service
Requires=memcached.service
# 重置所有断言，接着重新加入想要的条件
AssertPathExists=
AssertPathExists=/srv/www

[Service]
Nice=0
PrivateTmp=yes
```

注意， 对于单元配置片段， 如果想要移除列表选项(例如 `AssertPathExists=` 或 `ExecStart=`)中的某些项， 那么必须首先清空列表(设为空)，然后才能添加(剔除掉某些项之后)剩余的列表项。 注意，因为依赖关系列表(`After=` 之类)不能被重置为空，所以： (1)在配置片段(`.conf`)中只能添加依赖关系； (2)如果你想移除现有的依赖关系，并重新设定， 那么只能用第一种方法(先复制，然后直接修改复制后的副本)。





#### 参见

[systemd(1)](https://www.jinbuguo.com/systemd/systemd.html#), [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#), [systemd-system.conf(5)](https://www.jinbuguo.com/systemd/systemd-system.conf.html#), [systemd.special(7)](https://www.jinbuguo.com/systemd/systemd.special.html#), [systemd.service(5)](https://www.jinbuguo.com/systemd/systemd.service.html#), [systemd.socket(5)](https://www.jinbuguo.com/systemd/systemd.socket.html#), [systemd.device(5)](https://www.jinbuguo.com/systemd/systemd.device.html#), [systemd.mount(5)](https://www.jinbuguo.com/systemd/systemd.mount.html#), [systemd.automount(5)](https://www.jinbuguo.com/systemd/systemd.automount.html#), [systemd.swap(5)](https://www.jinbuguo.com/systemd/systemd.swap.html#), [systemd.target(5)](https://www.jinbuguo.com/systemd/systemd.target.html#), [systemd.path(5)](https://www.jinbuguo.com/systemd/systemd.path.html#), [systemd.timer(5)](https://www.jinbuguo.com/systemd/systemd.timer.html#), [systemd.scope(5)](https://www.jinbuguo.com/systemd/systemd.scope.html#), [systemd.slice(5)](https://www.jinbuguo.com/systemd/systemd.slice.html#), [systemd.time(7)](https://www.jinbuguo.com/systemd/systemd.time.html#), [systemd-analyze(1)](https://www.jinbuguo.com/systemd/systemd-analyze.html#), [capabilities(7)](http://man7.org/linux/man-pages/man7/capabilities.7.html), [systemd.directives(7)](https://www.jinbuguo.com/systemd/systemd.directives.html#), [uname(1)](http://man7.org/linux/man-pages/man1/uname.1.html)

### 四、systemd.target

#### 名称

systemd.target — 目标单元配置

#### 大纲

```
*`target`*.target
```



#### 描述

以 "`.target`" 为后缀的单元文件， 封装了一个由 systemd 管理的启动目标， 用于在启动过程中将一组单元汇聚到一个众所周知的同步点。

此类单元没有专用的配置选项。 [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#) 中描述了通用于所有单元类型的配置选项(亦称"配置指令"或"单元属性")， 它们位于 [Unit] 与 [Install] 小节。因为此类单元没有专用的配置选项， 所以并不存在专用的 [Target] 小节。

对于被目标单元汇聚的单元来说， 目标单元本身并不能提供任何额外的附加功能。 目标单元的功能仅仅是通过依赖关系将一组单元汇聚在一起， 形成一个同步点，并给这个同步点取一个众所周知的名称， 以便用作启动目标或其他单元的依赖。 目标单元非常适合用于替代传统的SysV运行级机制， 特别地，出于兼容性考虑， 类似 `runlevel3.target` 这样的目标单元， 应该专用于兼容传统SysV运行级的场合。 详见 [systemd.special(7)](https://www.jinbuguo.com/systemd/systemd.special.html#) 手册。



#### 自动依赖



##### 隐含依赖

target 单元没有隐含依赖。



##### 默认依赖

除非明确设置了 `DefaultDependencies=no` ，否则 target 单元将会自动添加下列依赖关系：

- 对通过 `Wants=` 或 `Requires=` 汇聚的单元的 `After=` 依赖(除非指定的单元中含有 `DefaultDependencies=no`)。 注意，必须明确的在 target 单元文件中定义对被汇聚单元的 `Wants=` 或 `Requires=` 依赖。 例如，如果你在 some.service 单元文件中定义了 `Wants=`some.target ， 那么并不会自动添加上述表示先后顺序的依赖关系。
- `Conflicts=shutdown.target` 与 `Before=shutdown.target` 依赖。



#### 例子



**例 1. 一个简单的独立目标单元**

```
# emergency-net.target

[Unit]
Description=Emergency Mode with Networking
Requires=emergency.target systemd-networkd.service
After=emergency.target systemd-networkd.service
AllowIsolate=yes
```

当在 target 单元中添加对其他单元的依赖时，务必要检查这些单元是否设置了 `DefaultDependencies=no` 。 对于服务单元来说，除非明确设置了 `DefaultDependencies=no` ， 否则将会自动获得 `Requires=sysinit.target`, `After=sysinit.target` 依赖。 在本例中，因为 `emergency.target` 与 `systemd-networkd.service` 都明确设置了 `DefaultDependencies=no` ， 也就是说它们都不包含对 `sysinit.target` 的依赖， 所以，很适合将它们引用到本例的 target 单元中。

要想进入本例所设置的"带网络的紧急维修模式"，可以使用 `systemctl isolate emergency-net.target` 命令，也可以使用 `systemd.unit=emergency-net.target` 内核引导选项。

如果某个单元将 `WantedBy=emergency-net.target` 加入到 `[Install]` 小节之中，那么在使用 **systemctl enable** 命令启用该单元时，将会同时确保该单元在 `emergency-net.target` 之前启动。 还可以通过 **systemctl add-wants** 命令在无须修改单元文件的情况下， 将任意单元添加为 `emergency.target` 的依赖。





#### 参见

[systemd(1)](https://www.jinbuguo.com/systemd/systemd.html#), [systemctl(1)](https://www.jinbuguo.com/systemd/systemctl.html#), [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#), [systemd.special(7)](https://www.jinbuguo.com/systemd/systemd.special.html#), [systemd.directives(7)](https://www.jinbuguo.com/systemd/systemd.directives.html#)

### 五、systemd.time

#### 名称

systemd.time — 时间与日期规范



#### 描述

在 systemd 环境中，时间戳(一个时间点)、时间长度(一段时间)、日历事件 的显示和赋值都有严格的规范和语法。



#### 时长的显示

"时长"是"时间长度"的简称，又被称为"时间间隔"，表示一段时间的长度。 显示为一个空格分隔的带有时间单位的时长序列。例如：

```
2h 30min
```

将序列中的每一段加起来就是最终的结果(150分钟)。 注意，时长的显示不受系统本地化设置的影响，永远使用英文时间单位。



#### 时长的赋值

systemd 在解析时长字符串(用于赋值)的时候， 接受与时长的显示类似的语法，不同之处在于可以省略空格。 可以理解的时间单位如下：

- usec, us, µs

  (微秒)

- msec, ms

  (毫秒)

- seconds, second, sec, s

  (秒)

- minutes, minute, min, m

  (分钟)

- hours, hour, hr, h

  (小时)

- days, day, d

  (天)

- weeks, week, w

  (星期)

- months, month, M

  (月)[=30.44天]

- years, year, y

  (年)[=365.25天]

如果没有指定时间单位，一般默认为秒，但是偶尔也有例外。 此外，在某些场合还可以接受纳秒单位("`ns`", "`nsec`")。 注意，时长的赋值不受系统本地化设置的影响，必须只能使用英文时间单位， 不可使用例如"小时/分钟/秒"之类的非英文时间单位。

下面是一些有效的时长字符串实例：

```
2 h
2hours
48hr
1y 12month
55s500ms
300ms20s 5day
```

出于测试和验证目的，可以使用 [systemd-analyze(1)](https://www.jinbuguo.com/systemd/systemd-analyze.html#) 的 **timespan** 命令规范化给定的时长字符串。



#### 时间戳的显示

时间戳表示的是一个独一无二的时间点， systemd 会按照本地时区格式化之后显示， 例如：

```
Fri 2012-11-23 23:02:15 CET
```

注意，时间戳的显示不受系统本地化设置的影响，并且表示"星期"的部分永远使用英文三字母缩写。

有时候，时间戳会以UTC时间(而非本地时间)显示， 此时，将会明确显示 "`UTC`" 时区标记。

有时候，时间戳会以微秒精度显示， 此时，表示"秒"的部分将会以带十进制小数的方式显示更精确的亚秒级时间。



#### 时间戳的赋值

systemd 在解析时间戳字符串(用于赋值)的时候，接受与时间戳的显示类似的语法。 不同之处在于： (1)尾部的"时区"部分，要么必须省略、要么必须丝毫不差的设为"`UTC`"三个大写字母、要么必须设为一个符合IANA格式的时区。 省略时区表示使用本机时区、设为"UTC"则表示使用世界统一时间， 使用 **timedatectl list-timezones** 命令(参见 [timedatectl(1)](https://www.jinbuguo.com/systemd/timedatectl.html#) 手册)可以按照IANA格式列出所有时区。 强烈建议使用"UTC"时区以保持最佳的兼容性(主要是为了避免夏令时/冬令时造成的麻烦)。 (2)头部的"星期"部分可以省略(强烈建议省略)。如果一定要指定这部分， 那么必须使用英文三字母缩写(例如"Wed")或英文全称(例如"Wednesday")，大小写无所谓，但是不得使用任何非英文表示法。 (3)"年-月-日"与"时:分:秒"两部分，可以省略二者之一，但是不可全部省略。若省略前者，则表示使用当前日期，若省略后者则表示使用"00:00:00"。 (4)"时:分:秒"部分，可以只省略":秒"，相当于使用":00"。 (5)"年-月-日"部分，其中的"年"可以省略为2位数字表示，相当于"20xx"(强烈反对此种用法)。

如果指定的"星期"与"年-月-日"(即使此部分已被省略)与实际不相符， 那么该时间戳将被视为无效。

除了接受上述语法之外， 还可以使用一些时间戳关键字： "`now`" 表示当前时间； "`today`", "`yesterday`", "`tomorrow`" 分别表示 今天/昨天/明天的零点(00:00:00)。

除了接受上述语法之外， 还可以使用一些相对时间表示法： 给一个时长(见上文)加上 "`+`" 前缀或者 "` left`" 后缀(注意有空格)， 表示以当前时间为基准向未来前进指定的时长； 给一个时长(见上文)加上 "`-`" 前缀 或者 "` ago`" 后缀(注意有空格)， 表示以当前时间为基准向过去倒退指定的时长；

最后，给一个时长(见上文)加上 "`@`" 前缀表示 相对于UNIX时间原点(1970-01-01 00:00:00 UTC)之后多长时间。

假定当前时间为北京时间[UTC+8] 2012-11-23 18:15:22 ， 系统时区 TZ=PRC (中华人民共和国的通用时区)。 下面是一些时间戳实例及其标准化形式：

```
  Fri 2012-11-23 11:12:13 → Fri 2012-11-23 11:12:13
      2012-11-23 11:12:13 → Fri 2012-11-23 11:12:13
  2012-11-23 11:12:13 UTC → Fri 2012-11-23 19:12:13
               2012-11-23 → Fri 2012-11-23 00:00:00
                 12-11-23 → Fri 2012-11-23 00:00:00
                 11:12:13 → Fri 2012-11-23 11:12:13
                    11:12 → Fri 2012-11-23 11:12:00
                      now → Fri 2012-11-23 18:15:22
                    today → Fri 2012-11-23 00:00:00
                today UTC → Fri 2012-11-23 16:00:00
                yesterday → Fri 2012-11-22 00:00:00
                 tomorrow → Fri 2012-11-24 00:00:00
tomorrow Pacific/Auckland → Thu 2012-11-23 19:00:00
                 +3h30min → Fri 2012-11-23 21:45:22
                      -5s → Fri 2012-11-23 18:15:17
                11min ago → Fri 2012-11-23 18:04:22
              @1395716396 → Tue 2014-03-25 03:59:56
```

注意，不能将其他不同时区的系统所显示的时间戳直接用于赋值。 因为无法识别UTC与本地时区之外的时间戳，所以其他系统所显示的时间戳可能会被错误的解析(除非那个系统的时区正好是"`UTC`")。

如果想以更高的微秒精度表示时间戳，"秒"部分可以用带十进制小数的方式表示更精确的亚秒级时间。 例如：

```
2014-03-25 03:59:56.654563
```

有时候， systemd 还可能显示相对时间戳(相对于当前时间或命令的调用时间)， 例如：

```
2 months 5 days ago
```

注意，systemd 显示的相对时间戳可以直接用于赋值(也就是可以被正确解析)。



#### 日历事件

所谓"日历事件"是指可以同时表达多个时间戳的一种特殊的表达式， 可以把它想象成一种专用于时间戳的正则表达式。 其语法是基于前述绝对时间戳语法的一种扩展。例如：

```
Thu,Fri 2012-*-1,5 11:12:13
```

表示： 2012年任意月份的1号或5号 且为周三或周五的日子的11点12分13秒

"星期"部分是可选的。 若指定， 则必须使用英文三字母缩写(例如"Wed")或英文全称(例如"Wednesday")， 大小写无关。可以使用 "`,`" 依次列出多个日子， 也可以使用 "`..`" 表示一个范围， 还可以将多个范围( "`..`" ) 用 "`,`" 依次列出。

对于"年-月-日"与"时:分:秒"两部分中的 每个子部分， 都可以： 使用 "`*`" 表示匹配任意值、 使用 "`,`" 依次列出多个值、 使用 "/整数" 后缀表示以此整数为间隔不断向后重复跳跃(例如在表示分钟的部分"3/10"等价于"3,13,23,33,43,53")、 使用 "`..`" 表示一个范围。 最后， 还可以用逗号(,)依次列出多个重复(/)与范围(..)。

在日期部分还可以使用 "`~`" 表示一个月中的"倒数第几天"。 例如 "`*-02~03`" 表示"2月的倒数第3天"， "`Mon *-05~07/1`" 表示"5月的最后一个星期一"。

注意，"秒"部分比较特殊， 可以使用十进制小数以表示更高的精度(最多六位小数)， 例如"3.33/10.05"等价于"3.33,13.38,23.43,33.48,43.53,53.58"。

若省略了"年-月-日" 则等价于当前日期； 若省略了"时:分:秒"则等价于"00:00:00"； 若省略了":秒"则等价于":00"

"时区"部分遵守与时间戳一样的规则， 要么必须省略、要么必须丝毫不差的设为"`UTC`"三个大写字母、要么必须设为一个符合IANA格式的时区。 省略时区表示使用本机时区，为了保持最佳的兼容性，强烈建议使用"UTC"时区(世界统一时间)。

下面这些左侧的特殊表达式可以用作右侧的标准化形式的缩写：

```
    minutely → *-*-* *:*:00
      hourly → *-*-* *:00:00
       daily → *-*-* 00:00:00
     monthly → *-*-01 00:00:00
      weekly → Mon *-*-* 00:00:00
      yearly → *-01-01 00:00:00
   quarterly → *-01,04,07,10-01 00:00:00
semiannually → *-01,07-01 00:00:00
   
```

下面是一些日历事件的实例及其 标准化形式：

```
  Sat,Thu,Mon..Wed,Sat..Sun → Mon..Thu,Sat,Sun *-*-* 00:00:00
      Mon,Sun 12-*-* 2,1:23 → Mon,Sun 2012-*-* 01,02:23:00
                    Wed *-1 → Wed *-*-01 00:00:00
           Wed..Wed,Wed *-1 → Wed *-*-01 00:00:00
                 Wed, 17:48 → Wed *-*-* 17:48:00
Wed..Sat,Tue 12-10-15 1:2:3 → Tue..Sat 2012-10-15 01:02:03
                *-*-7 0:0:0 → *-*-07 00:00:00
                      10-15 → *-10-15 00:00:00
        monday *-12-* 17:00 → Mon *-12-* 17:00:00
  Mon,Fri *-*-3,1,2 *:30:45 → Mon,Fri *-*-01,02,03 *:30:45
       12,14,13,12:20,10,30 → *-*-* 12,13,14:10,20,30:00
            12..14:10,20,30 → *-*-* 12..14:10,20,30:00
  mon,fri *-1/2-1,3 *:30:45 → Mon,Fri *-01/2-01,03 *:30:45
             03-05 08:05:40 → *-03-05 08:05:40
                   08:05:40 → *-*-* 08:05:40
                      05:40 → *-*-* 05:40:00
     Sat,Sun 12-05 08:05:40 → Sat,Sun *-12-05 08:05:40
           Sat,Sun 08:05:40 → Sat,Sun *-*-* 08:05:40
           2003-03-05 05:40 → 2003-03-05 05:40:00
 05:40:23.4200004/3.1700005 → *-*-* 05:40:23.420000/3.170001
             2003-02..04-05 → 2003-02..04-05 00:00:00
       2003-03-05 05:40 UTC → 2003-03-05 05:40:00 UTC
                 2003-03-05 → 2003-03-05 00:00:00
                      03-05 → *-03-05 00:00:00
                     hourly → *-*-* *:00:00
                      daily → *-*-* 00:00:00
                  daily UTC → *-*-* 00:00:00 UTC
                    monthly → *-*-01 00:00:00
                     weekly → Mon *-*-* 00:00:00
    weekly Pacific/Auckland → Mon *-*-* 00:00:00 Pacific/Auckland
                     yearly → *-01-01 00:00:00
                   annually → *-01-01 00:00:00
                      *:2/3 → *-*-* *:02/3:00
```

定时器单元会使用日历事件，详见 [systemd.timer(5)](https://www.jinbuguo.com/systemd/systemd.timer.html#) 手册。

出于测试和验证目的，可以使用 [systemd-analyze(1)](https://www.jinbuguo.com/systemd/systemd-analyze.html#) 的 **calendar** 命令规范化给定的日历事件。 此工具还会计算出给定日历事件的下一个过期时间。



#### 参见

[systemd(1)](https://www.jinbuguo.com/systemd/systemd.html#), [journalctl(1)](https://www.jinbuguo.com/systemd/journalctl.html#), [systemd.timer(5)](https://www.jinbuguo.com/systemd/systemd.timer.html#), [systemd.unit(5)](https://www.jinbuguo.com/systemd/systemd.unit.html#), [systemd.directives(7)](https://www.jinbuguo.com/systemd/systemd.directives.html#), [systemd-analyze(1)](https://www.jinbuguo.com/systemd/systemd-analyze.html#)