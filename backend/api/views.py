
from rest_framework.permissions import AllowAny
from rest_framework.response import Response
from rest_framework import generics
from rest_framework import status

from .validators import UserModel
from .logic import ZodiacSign
from . import serializers


class GetContentList(generics.ListAPIView):
    permission_classes = (AllowAny, )
    serializer_class = serializers.GetContentSerializer

    def list(self, request, *args, **kwargs):
        filter = self._set_filter(request)
        self._set_queryset(filter)
        return super().list(request, *args, **kwargs)

    def _set_queryset(self, filter):
        self.queryset = UserModel.objects.filter(**filter).all()

    def _set_filter(self, request):
        ser = self.serializer_class(data=request.query_params)
        ser.is_valid()
        return {key : value for key, value in ser.validated_data.items() if value}


class CreateContent(generics.CreateAPIView, ZodiacSign):
    permission_classes = (AllowAny, )

    def post(self, request, *args, **kwargs):
        serializer = serializers.CreateContentSerializer(data=request.data)
        if not serializer.is_valid():
            return Response(data=serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        self.validated_data = serializer.validated_data
        self._set_zodiac_sign()

        UserModel.objects.create(**self.validated_data)
        return Response(data=self.validated_data, status=status.HTTP_201_CREATED)


class UpdateContent(generics.UpdateAPIView, ZodiacSign):
    permission_classes = (AllowAny, )

    def put(self, request, *args, **kwargs):
        serializer = serializers.UpdateContentSerializer(data=request.data)
        if not serializer.is_valid():
            return Response(data=serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        user = UserModel.objects.get(email=serializer.validated_data['email'])

        self.validated_data = serializer.validated_data

        if self.validated_data.get('birthday', None) is not None:
            self._set_zodiac_sign()

        UserModel.objects.filter(pk=user.pk).update(**self.validated_data)

        user.refresh_from_db()
        data = serializers.GetContentSerializer(user).data
        return Response(data=data, status=status.HTTP_202_ACCEPTED)


class DeleteContent(generics.DestroyAPIView):
    permission_classes = (AllowAny, )

    def delete(self, request, *args, **kwargs):
        serializer = serializers.DeleteContentSerializer(data=request.data)
        if not serializer.is_valid():
            return Response(data=serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        user = UserModel.objects.get(email=serializer.validated_data['email'])
        user.delete()
        data = serializers.GetContentSerializer(user).data
        return Response(data=data, status=status.HTTP_200_OK)
