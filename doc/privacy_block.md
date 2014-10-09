# API Reference (1.0)
---

## 1. privacy_block (ajax)

### url
http://x.x.x.x/api/1.0/privacy_block.json

### 支持格式
JSON

### HTTP请求方式
GET  
PUT

### 是否需要登录
是

### 请求参数
请求|参数|必选|类型及范围|说明
---|---|:-:|---|---|---
GET|items|是|array: ['region1', 'region2']|需要查询的隐私遮盖区域的名称
PUT|items|是|object:|要设置的隐私遮盖区域的名称，是否启用，，X/Y坐标，宽高和颜色值

### 注意事项
无

### 调用样例
GET http://x.x.x.x/api/1.0/privacy_block.json?items[]=region1&items[]=region2  
PUT http://x.x.x.x/api/1.0/privacy_block.json json_data

### 返回结果
JSON示例  
GET

	{
		'items': {
			region1: {
				"enabled": false,
				"left":10,
				"top":20,
				"width":10,
				"height":20,
				"color": {
					"red": 0,
					"green": 0,
					"blue": 0,
					"alpha": 0
                }
			},
			region2: {
				"enabled": false,
				"left":10,
				"top":20,
				"width":10,
				"height":20,
				"color": {
					"red": 0,
					"green": 0,
					"blue": 0,
					"alpha": 0
                }
			}
		}
	}
	
PUT

	{'success': 'true' | 'false'}
	
### 返回字段说明
返回值字段|字段类型|字段说明
---|---|---
enabled|boolean|OSD设置项名称
left|int|区域的左边距，千分比
top|int|区域的上边距，千分比
width|int|区域的宽度，千分比
height|int|区域的高度，千分比
red|int|区域颜色的红色分量，0-255
green|int|区域颜色的绿色分量，0-255
blue|int|区域颜色的蓝色分量，0-255
alpha|int|区域颜色的透明度分量，0-255

## 2. osd (message)

### 2.1 get_privacy_block
#### request
    {
		'head': {
            'action': 'get_privacy_block',
            'version': '1.0'
		},
        'body': {
            'items': [
                'region1',
                'region2'
            ]
        }
    }
#### response
    {
		'head': {
            'action': 'get_privacy_block',
            'version': '1.0',
            'code': '0'
		},
        'body': {
            'items': {
				region1: {
					"enabled": false,
					"left":10,
					"top":20,
					"width":10,
					"height":20,
					"color": {
						"red": 0,
						"green": 0,
						"blue": 0,
						"alpha": 0
                	}
				},
				region2: {
					"enabled": false,
					"left":10,
					"top":20,
					"width":10,
					"height":20,
					"color": {
						"red": 0,
						"green": 0,
						"blue": 0,
						"alpha": 0
                	}
				}
			}
		}
    }
---
### 2.2 set_privacy_block
#### request
    {
        'head': {
            'action': 'set_privacy_block',
            'version': '1.0'
        },
        'body': {
			'items': {
				region1: {
					"enabled": false,
					"left":10,
					"top":20,
					"width":10,
					"height":20,
					"color": {
						"red": 0,
						"green": 0,
						"blue": 0,
						"alpha": 0
                	}
				},
				region2: {
					"enabled": false,
					"left":10,
					"top":20,
					"width":10,
					"height":20,
					"color": {
						"red": 0,
						"green": 0,
						"blue": 0,
						"alpha": 0
                	}
				}
			}
        }
    }
#### response
    {
		'head': {
            'action': 'set_privacy_block',
            'version': '1.0',
            'code': '0'
        },
        'body': {
        }
    }