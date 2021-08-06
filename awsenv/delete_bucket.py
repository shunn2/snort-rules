import boto3
from botocore.exceptions import ClientError

BUCKET_NAME = 'bob10-4249-pub'
AWS_ACCESS_KEY = 'AKIAWHPSCFE25U35HYPB'
AWS_SECRET_ACCESS_KEY = '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'

client = boto3.client('s3')
obj_list = client.list_objects(Bucket = BUCKET_NAME) ##객체들
contents_list = obj_list['Contents']

for content in contents_list:
    key = content['Key']
    client.delete_objects(Bucket = BUCKET_NAME, Delete ={'Objects': [{'Key': key,}]}, RequestPayer = 'requester')

obj_v_list = client.list_object_versions(Bucket = BUCKET_NAME)

s3 = boto3.resource('s3')
s3_bucket = s3.Bucket(BUCKET_NAME)
s3_bucket.object_versions.delete()

client.delete_bucket(Bucket = BUCKET_NAME)


