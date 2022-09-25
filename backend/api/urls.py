
from django.urls import path

from . import views

urlpatterns = [
    path('get-content/', views.GetContentList.as_view()),
    path('create-content/', views.CreateContent.as_view()),
    path('update-content/', views.UpdateContent.as_view()),
    path('delete-content/', views.DeleteContent.as_view()),
]