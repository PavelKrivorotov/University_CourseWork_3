
from rest_framework import serializers

from . import validators


class GetContentSerializer(serializers.Serializer):
    email = serializers.EmailField(read_only=True)
    first_name = serializers.CharField(max_length=150, read_only=True)
    last_name = serializers.CharField(max_length=150, required=False)
    birthday = serializers.DateField(required=False)
    zodiac = serializers.CharField(max_length=11, required=False)


class CreateContentSerializer(serializers.Serializer):
    email = serializers.EmailField(validators=[validators.check_email_not_exists])
    first_name = serializers.CharField(max_length=150)
    last_name = serializers.CharField(max_length=150)
    birthday = serializers.DateField()
    zodiac = serializers.CharField(max_length=11, read_only=True)


class UpdateContentSerializer(serializers.Serializer):
    email = serializers.EmailField(validators=[validators.check_email_exists])
    first_name = serializers.CharField(max_length=150, required=False)
    last_name = serializers.CharField(max_length=150, required=False)
    birthday = serializers.DateField(required=False)
    zodiac = serializers.CharField(max_length=11, read_only=True)


class DeleteContentSerializer(serializers.Serializer):
    email = serializers.EmailField(validators=[validators.check_email_exists])
    first_name = serializers.CharField(max_length=150, read_only=True)
    last_name = serializers.CharField(max_length=150, read_only=True)
    birthday = serializers.DateField(read_only=True)
    zodiac = serializers.CharField(max_length=11, read_only=True)
