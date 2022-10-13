
from datetime import datetime

from django.contrib.auth import get_user_model

from rest_framework.serializers import ValidationError


valid_words_en = [
    'a', 'b', 'c', 'd', 'e',
    'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y',
    'z'
]

valid_words_ru = [
    'а', 'б', 'в', 'г', 'д',
    'е', 'ё', 'ж', 'з', 'и',
    'й', 'к', 'л', 'м', 'н',
    'о', 'п', 'р', 'с', 'т',
    'у', 'ф', 'х', 'ц', 'ч',
    'ш', 'щ', 'ъ', 'ы', 'ь',
    'э', 'ю', 'я'
]


UserModel = get_user_model()


def check_email_exists(email):
    if UserModel.objects.filter(email=email).exists():
        return email
    raise ValidationError('This E-mail address doese not exists!')


def check_email_not_exists(email):
    if not UserModel.objects.filter(email=email).exists():
        return email
    raise ValidationError('This E-mail address doese exists!')


def check_valid_name_en(name):
    for word in name:
        if word not in valid_words_en:
            raise ValidationError("Not a correct symbols! You can use only Latian symbols.")
    return name


def check_valid_name_ru(name):
    for word in name:
        if word not in valid_words_ru:
            raise ValidationError("Not a correct symbols! You can use only Cyrillic symbols.")
    return name


def check_valid_birthday(birthday):
    if birthday > datetime.date(datetime.now()):
        raise ValidationError('Not a correct birthday!')
    return birthday

