#include "DataRequestBase.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Runtime/Json/Public/Json.h"

TSharedPtr<IHttpRequest> DataRequestBase::CreateHttpRequest(const FString& urlReq)
{
	auto request = FHttpModule::Get().CreateRequest();

	request->SetHeader("Content-Type", "application/json");

	if(!ID.IsEmpty())
		request->SetHeader("UserId", ID);

	request->SetURL(GetServerUrl(urlReq));
	
	return request;
}

FString DataRequestBase::CombineURL(const FString& urlReq)
{
	return ServerUrl / urlReq;
}

FString DataRequestBase::GetServerUrl(const FString& urlReq)
{
	const FString JsonPath = FPaths::ProjectConfigDir() / "setting.json";

	FString data;
	
	if (!FFileHelper::LoadFileToString(data, *JsonPath)) {
		UE_LOG(LogTemp, Error, TEXT("Not setting!"));
		return "";
	}

	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(data);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (!JsonObject.Get()->TryGetStringField("ServerName", ServerUrl)) {
			UE_LOG(LogTemp, Error, TEXT("Not parametr'ServerName' !"));
			return "";
		}
	}

	return CombineURL(urlReq);
}
