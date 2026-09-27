require 'optparse'
require 'httparty'
require 'colorize'
def make_request(host, action)

	headers = {
		"sourpatchkids": "sourpatchkids",

	}
	host = host + action
	rsp = HTTParty.get(host, headers: headers).body
	case action
	when "status"
		rsp.split(":").each do |s|
			if s.match?(/true/)
				data = s.split("_")
				puts "#{data[0]} is enabled.".green
			elsif s.match?(/false/)
				data = s.split("_")
				puts "#{data[0]} is disabled.".red
			end
		end
	end
end
options = {
	host: "localhost"
}

actions = {
	"1" => "cronjob",
	"2" => "shell",
	"3" => "clean",
	"4" => "status",
	"5" => "info",
	"6" => "users"
}
# 
OptionParser.new do |opts|
  opts.banner = "Usage: example.rb [options]"

  opts.on("-h", "--host HOST", "Defines the host") do |h|
    options[:host] = h || "localhost"
  end

  opts.on("-a", "--action ACTION", "Sets the action" ) do |a|
  	options[:action] = a
  end
  opts.on("-v", "--verbose", "Run in verbose mode") do
    options[:verbose] = true
  end
end.parse! 



unless options[:host].match?(/http[s]?:\/\//)
	new_host = "http://#{options[:host]}/errorteacups?url="
	options[:host] = new_host
end


if options[:action].nil?
	actions.each do |number, action|
		puts "#{number})\s#{action}"
	end
	puts "\n\n\nYou need an action."
end

if options[:action].match?(/\d+/)
	options[:action] = actions.fetch(options[:action].to_s)
end


make_request(options[:host], options[:action])