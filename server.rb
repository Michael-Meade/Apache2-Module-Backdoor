require 'sinatra'
set :port, 9999
post '/lol' do 
	puts request.body.read
	
end