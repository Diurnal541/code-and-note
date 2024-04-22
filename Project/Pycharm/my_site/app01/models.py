from django.db import models

# Create your models here.
class UserInfo(models.Model):
    name = models.CharField(max_length=64)
    password = models.CharField(max_length=32)
    age = models.IntegerField()

    data = models.IntegerField(null=True, blank=True)

class Department(models.Model):
    title = models.CharField(max_length=64)
