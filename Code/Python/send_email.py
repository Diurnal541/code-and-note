# 1.将Python内置的模块（功能导入）
import smtplib
from email.mime.text import MIMEText
from email.utils import formataddr

# 2.构建邮件内容
msg = MIMEText("哥哥约吗，180一晚","html","utf-8") # 内容
msg["From"] = formataddr(["黑丝美女","aaa821467574@126.com"]) # 自己名字/自己邮箱
msg["to"] = "3312305626@qq.com" # 目标邮箱
msg["Subject"] = "180一天" # 主题

# 3.发送邮件
server = smtplib.SMTP_SSL("smtp.126.com")
server.login("aaa821467574@126.com", "WJQTWLPPWLTFAUVY") # 账户和授权码
server.sendmail("aaa821467574@126.com", "3312305626@qq.com", msg.as_string()) # 自己的邮箱/目标邮箱/内容
server.quit()

# 3312305626@qq.com
