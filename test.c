#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// ChatGPT API 访问令牌
#define API_TOKEN "sk-proj-oYZIokTYINHZpLq84ZVAT3BlbkFJ47SBLYjP0oyAWbTMtNmd"

// ChatGPT API 端点
#define API_ENDPOINT "https://api.openai.com/v1/chat/completions"

// ChatGPT 提示语句
#define PROMPT "你想问什么？"

// 发送 POST 请求
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((char *)userp)[0] = '\0';
    strncat((char *)userp, contents, size * nmemb);
    return size * nmemb;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    char post_fields[5000];
    char response[5000];

    // 初始化 libcurl
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing curl\n");
        return 1;
    }

    // 构建 POST 请求数据
    snprintf(post_fields, sizeof(post_fields), "{\"model\":\"text-davinci-002\",\"prompt\":\"%s\"}", PROMPT);

    // 设置 libcurl 选项
    curl_easy_setopt(curl, CURLOPT_URL, API_ENDPOINT);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer " API_TOKEN);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // 发送请求
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // 输出回复
        printf("ChatGPT回答：%s\n", response);
    }

    // 清理 libcurl 资源
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return 0;
}
