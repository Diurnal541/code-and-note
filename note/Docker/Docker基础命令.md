# Docker基础命令

1. 镜像相关

   docker images：查看本机已有镜像

   REPOSITORY：镜像名

   TAG：镜像标签

   IMAGE：镜像ID

   CREATED：镜像创建时间

   SIZE：镜像大小

   docker pull 镜像名：拉取镜像

   docker rmi 镜像ID/名：删除本地镜像

   docker tag：设置镜像标签

   镜像构建：

   docker commit [选项] 容器ID/名称 仓库名称:标签 # 基于已有容器创建镜像

   docker build # 使用Dockerfile来创建一个镜像

2. 容器相关

   1. docker ps [选项] # 列出正在运行的容器

      常用选项：

      -n int 列出最后创建的n个容器

      -a 列出所有容器

      -l 最新创建的容器

   2. docker run [选项]\<镜像名:版本号>

      重要的选项：

      --name \<容器名称> 用来指定容器的名称

      -d 后台运行容器

      --rm 容器挂掉后自动删除

      -v 指定挂载点

      -it 以交互模式连接容器，并分配一个终端

      -p 端口映射

   3. docker exec -it  容器名/ID bash # 使用bash终端进入运行的容器

   4. docker stop/start/restart/exit 容器名/ID # 停止，启动，重启，退出容器

   5. docker rm [选项]  容器名/ID  # 删除挂掉的容器，加上-f可以强制删除启动着的容器

   6. docker commit  [选项]  容器ID/名称 仓库名称:标签    # 修改后的容器导出为镜像

   7. 主机和容器之间的文件交换：

      docker cp 主机文件名 容器名:文件名 # 主机文件复制到容器

      docker cp 容器名:文件名 # 容器文件复制到主机

   8. 查看信息相关：
      docker inspect # 查看容器元数据

      docker logs # 查看容器的日志

3. 仓库相关

   docker login 镜像仓库地址 [选项] # 登录镜像仓库，可用-u -p分别指定登录的用户名和密码（已经注册过dockerhub的前提下）

   docker push 镜像 # 上传镜像到仓库

   上传前我们需要先登录，镜像名字我们要用tag命令修改规范

