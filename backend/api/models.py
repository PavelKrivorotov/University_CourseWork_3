
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager
from django.utils.translation import gettext_lazy as _
from django.db import models


class UserManager(BaseUserManager):
    def create_user(self, email, first_name, last_name, birthday, password=None):
        if not (email and first_name and last_name and birthday):
            raise ValueError('User must have an email, first_name, last_nmae and birthday parametrs!')

        user = self.model(email=self.normalize_email(email), first_name=first_name,
            last_name=last_name, birthday=birthday)
        
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_superuser(self, email, first_name, last_name, birthday, password=None):
        user = self.create_user(email=email, first_name=first_name, last_name=last_name,
            birthday=birthday, password=password)

        user.is_admin = True
        user.save(using=self._db)
        return user


class User(AbstractBaseUser):
    email = models.EmailField('Email', unique=True)
    first_name = models.CharField('First Name', max_length=150)
    last_name = models.CharField('Last Name', max_length=150)
    birthday = models.DateField('Birthday')
    zodiac = models.CharField('Zodiac', max_length=11, null=True)

    is_admin = models.BooleanField('Admin', default=False)
    is_staff = models.BooleanField('Staff', default=False)
    is_active = models.BooleanField('Active', default=True)

    objects = UserManager()

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = ['first_name', 'last_name', 'birthday']

    class Meta:
        ordering = ('pk', )

    def __str__(self):
        return f'{self.first_name} {self.last_name}'