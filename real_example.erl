%%% Copyright (c) 2017, Mathieu Kerjouan <contact@steepath.eu>
%%%
%%% Permission to use, copy, modify,  and distribute this software for
%%% any purpose with  or without fee is hereby  granted, provided that
%%% the above  copyright notice and  this permission notice  appear in
%%% all copies.
%%%
%%% THE  SOFTWARE IS  PROVIDED "AS  IS" AND  THE AUTHOR  DISCLAIMS ALL
%%% WARRANTIES  WITH REGARD  TO  THIS SOFTWARE  INCLUDING ALL  IMPLIED
%%% WARRANTIES OF MERCHANTABILITY  AND FITNESS. IN NO  EVENT SHALL THE
%%% AUTHOR   BE  LIABLE   FOR  ANY   SPECIAL,  DIRECT,   INDIRECT,  OR
%%% CONSEQUENTIAL  DAMAGES OR  ANY DAMAGES  WHATSOEVER RESULTING  FROM
%%% LOSS OF  USE, DATA OR PROFITS,  WHETHER IN AN ACTION  OF CONTRACT,
%%% NEGLIGENCE  OR  OTHER  TORTIOUS  ACTION,  ARISING  OUT  OF  OR  IN
%%% CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

-module(real_example).
-export([start/1, start_link/1, start_monitor/1]).

% start a new process
start(Path) ->
  spawn(fun() 
    -> start_loop(Path) end).

% start a new linked process
start_link(Path) ->
  spawn_link(fun() 
    -> start_loop(Path) end).

% start a new monitored process
start_monitor(Path) ->
  spawn_monitor(fun() 
    -> start_loop(Path) end).

% init loop
start_loop(Path) ->
  % set ports options, received data as binary
  % and all first 4 bytes are the size of the 
  % binary packet
  PortOpts = [binary,{packet, 4}],

  % open port defined by Path
  Port = erlang:open_port({spawn, Path}
                         ,PortOpts),

  % Enter in main loop
  loop(Port).

% main loop
loop(Port) ->
  receive
    % when we receive a message from Port
    {Port, {data, X}} ->
      % We encode it...
      Encoded = erlang:binary_to_term(X),

      % And print it on stdout
      io:format("receive data: ~p~n"
               ,[Encoded]),
      loop(Port);

    % when run command is received
    % we send 'l' command to the port
    run ->
      erlang:port_command(Port, <<"l">>), 
      loop(Port);

    % return info concerning connected port
    info ->
      io:format("~p~n", [erlang:port_info(Port)]),
      loop(Port);

    % just quit the process
    exit ->
      ok;

    % if we receive another pattern
    % we just print it
    _Else ->
      io:format("Received wrong patter: ~p~n"
               ,[_Else]),
      loop(Port)
  end.
