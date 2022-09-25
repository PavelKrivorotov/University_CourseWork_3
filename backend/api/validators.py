
from django.contrib.auth import get_user_model

from rest_framework.serializers import ValidationError


UserModel = get_user_model()

def check_email_exists(email):
    if UserModel.objects.filter(email=email).exists():
        return email
    raise ValidationError('This E-mail address doese not exists!')


def check_email_not_exists(email):
    if not UserModel.objects.filter(email=email).exists():
        return email
    raise ValidationError('This E-mail address doese exists!')