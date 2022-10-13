
from rest_framework.permissions import AllowAny
from rest_framework.response import Response
from rest_framework import generics
from rest_framework import status

from .validators import UserModel
from .logic import ZodiacSign
from . import serializers
from .jsonresponse import DictAnswer


class GetContentList(generics.ListAPIView):
    permission_classes = (AllowAny, )
    serializer_class = serializers.GetContentSerializer

    def list(self, request, *args, **kwargs):
        ser = self.serializer_class(data=request.query_params)
        if not ser.is_valid():
            data = DictAnswer(error=True, errors=ser.errors)
            return Response(data=data.get_data, status=status.HTTP_400_BAD_REQUEST)

        filter = {key : value for key, value in ser.validated_data.items() if value}
        self._set_queryset(filter)
        
        queryset = self.filter_queryset(self.get_queryset())
        serializer = self.get_serializer(queryset, many=True)

        data = DictAnswer(many=True, content=serializer.data)
        return Response(data=data.get_data)

    def _set_queryset(self, filter):
        self.queryset = UserModel.objects.filter(**filter).all()


class CreateContent(generics.CreateAPIView, ZodiacSign):
    permission_classes = (AllowAny, )

    def post(self, request, *args, **kwargs):
        serializer = serializers.CreateContentSerializer(data=request.data)
        if not serializer.is_valid():
            data = DictAnswer(error=True, errors=serializer.errors)
            return Response(data=data.get_data, status=status.HTTP_400_BAD_REQUEST)

        self.validated_data = serializer.validated_data
        self._set_zodiac_sign()

        UserModel.objects.create(**self.validated_data)
        data = DictAnswer(content=self.validated_data)
        return Response(data=data.get_data, status=status.HTTP_201_CREATED)


class UpdateContent(generics.UpdateAPIView, ZodiacSign):
    permission_classes = (AllowAny, )

    def put(self, request, *args, **kwargs):
        serializer = serializers.UpdateContentSerializer(data=request.data)
        if not serializer.is_valid():
            data = DictAnswer(error=True, errors=serializer.errors)
            return Response(data=data.get_data, status=status.HTTP_400_BAD_REQUEST)

        user = UserModel.objects.get(email=serializer.validated_data['email'])

        self.validated_data = serializer.validated_data

        if self.validated_data.get('birthday', None) is not None:
            self._set_zodiac_sign()

        UserModel.objects.filter(pk=user.pk).update(**self.validated_data)

        user.refresh_from_db()
        user_data = serializers.GetContentSerializer(user).data
        data = DictAnswer(content=user_data)
        return Response(data=data.get_data, status=status.HTTP_202_ACCEPTED)


class DeleteContent(generics.DestroyAPIView):
    permission_classes = (AllowAny, )

    def delete(self, request, *args, **kwargs):
        serializer = serializers.DeleteContentSerializer(data=request.query_params)
        if not serializer.is_valid():
            data = DictAnswer(error=True, errors=serializer.errors)
            return Response(data=data.get_data, status=status.HTTP_400_BAD_REQUEST)

        user = UserModel.objects.get(email=serializer.validated_data['email'])
        user.delete()
        user_data = serializers.GetContentSerializer(user).data
        data = DictAnswer(content=user_data)
        return Response(data=data.get_data, status=status.HTTP_200_OK)
