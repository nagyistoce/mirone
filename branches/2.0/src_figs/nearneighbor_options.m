function varargout = nearneighbor_options(varargin)
% varargin   command line arguments to nearneighbor_options (see VARARGIN)

%	Copyright (c) 2004-2006 by J. Luis
%
%	This program is free software; you can redistribute it and/or modify
%	it under the terms of the GNU General Public License as published by
%	the Free Software Foundation; version 2 of the License.
%
%	This program is distributed in the hope that it will be useful,
%	but WITHOUT ANY WARRANTY; without even the implied warranty of
%	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%	GNU General Public License for more details.
%
%	Contact info: w3.ualg.pt/~jluis/mirone
% --------------------------------------------------------------------
 
hObject = figure('Tag','figure1','Visible','off');
nearneighbor_options_LayoutFcn(hObject);
handles = guihandles(hObject);
move2side(hObject,'right')
 
handles.command = cell(20,1);

if ~isempty(varargin)	old_cmd = varargin{1};	end

if ~isempty(old_cmd)        % Decode old command and initialize corresponding boxes
    [tok,rem] = strtok(varargin{1});
    tmp{1} = tok;         i = 2;
    while (rem)
        [tok,rem] = strtok(rem);
        tmp{i} = tok;     i = i + 1;
    end
    for i=1:length(tmp)
        switch tmp{i}(2)
            case 'E'
                handles.command{5} = [' ' tmp{i}];
                set(handles.edit_EmptyNodes,'String',tmp{i}(3:end))
            case 'L'
                switch tmp{i}(3:end);
                    case '',    val = 1;
                    case 'x',   val = 2;
                    case 'y',   val = 3;
                    case 'xy',  val = 4;
                    case 'g',   val = 5;
                end
                handles.command{7} = [' ' tmp{i}];
                set(handles.popup_BoundaryCondition,'Value',val)
            case 'N'
                handles.command{9} = [' ' tmp{i}];
                set(handles.edit_Nsectrors,'String',tmp{i}(3:end))
            case 'W'
                handles.command{11} = [' ' tmp{i}];
                set(handles.checkbox_FourColumns,'Value',1)
        end
    end
    set(handles.edit_ShowCommand, 'String', [handles.command{5:end}]);
end

handles.output = hObject;
guidata(hObject, handles);

% Make the GUI modal
%set(handles.figure1,'WindowStyle','modal')
set(hObject,'Visible','on');
% UIWAIT makes nearneighbor_options_export wait for user response (see UIRESUME)
uiwait(handles.figure1);

handles = guidata(hObject);
varargout{1} = handles.output;
delete(handles.figure1);

function edit_EmptyNodes_CB(hObject, handles)
handles.command{5} = [' -E' get(hObject,'String')];
set(handles.edit_ShowCommand, 'String', [handles.command{5:end}]);
guidata(hObject, handles);

function pushbutton_help_E_CB(hObject, handles)
message = {'Set the value assigned to empty nodes [NaN].'};
helpdlg(message,'Help -E option');

function popup_BoundaryCondition_CB(hObject, handles)
val = get(hObject,'Value');     str = get(hObject, 'String');
switch str{val};
    case ''
        handles.command{7} = '';
    case 'x'
        handles.command{7} = ' -Lx';
    case 'y'
        handles.command{7} = ' -Ly';
    case 'xy'
        handles.command{7} = ' -Lxy'; 
    case 'g'
        handles.command{7} = ' -Lg';
end
set(handles.edit_ShowCommand, 'String', [handles.command{5:end}]);
guidata(hObject, handles);
       
function pushbutton_help_L_CB(hObject, handles)
message = {'Boundary condition flag may be x or y or xy indicating data is periodic'
           'in range of x or y or both set by -R (the grids limits in the previous'
           'window), or flag may be g indicating geographical conditions (x and y'
           'are lon and lat). [Default is no boundary conditions].'};
helpdlg(message,'Help -L option');

function edit_Nsectrors_CB(hObject, handles)
xx = get(hObject,'String');
if str2double(xx) < 1 || isnan(str2double(xx))
    set(hObject,'String','4')
    handles.command{9} = '';
else
    handles.command{9} = [' -N' num2str(fix(str2double(get(hObject,'String'))))];
    set(hObject,'String',num2str(fix(str2double(get(hObject,'String')))))
end
set(handles.edit_ShowCommand, 'String', [handles.command{5:end}]);
guidata(hObject, handles);

function pushbutton_help_N_CB(hObject, handles)
message = {'The circular area centered on each node is divided into several sectors.'
           'Average values will only be computed if there is at least one value inside'
           'each of the sectors for a given node. Nodes that fail this test are'
           'assigned the value NaN (but see Empty nodes -E). [Default is quadrant'
           'search, i.e., sectors = 4]. Note that only the nearest value per sector'
           'enters into the averaging, not all values inside the circle.'};
helpdlg(message,'Help -N option');

function checkbox_FourColumns_CB(hObject, handles)
tmp = get(hObject,'Value');
if tmp
    handles.command{11} = ' -W';
else
    handles.command{11} = '';
end
set(handles.edit_ShowCommand, 'String', [handles.command{5:end}]);
guidata(hObject, handles);

function pushbutton_help_W_CB(hObject, handles)
message = {'Input data have a 4th column containing observation point weights.'
           'These are multiplied with the geometrical weight factor to determine'
           'the actual weights used in the calculations.'};
helpdlg(message,'Help -W option');

function popup_FormatInput_CB(hObject, handles)

function edit_ShowCommand_CB(hObject, handles)

function pushbutton_Cancel_CB(hObject, handles)
handles.output = '';        % User gave up, return nothing
guidata(hObject, handles);
uiresume(handles.figure1);

function pushbutton_OK_CB(hObject, handles)
	handles.output = get(handles.edit_ShowCommand, 'String');
	guidata(hObject,handles)
	uiresume(handles.figure1);

% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, evt)
handles = guidata(hObject);
if isequal(get(handles.figure1, 'waitstatus'), 'waiting')
    % The GUI is still in UIWAIT, us UIRESUME
    handles.output = '';        % User gave up, return nothing
    guidata(hObject, handles);
    uiresume(handles.figure1);
else
    % The GUI is no longer waiting, just close it
    handles.output = '';        % User gave up, return nothing
    guidata(hObject, handles);
    delete(handles.figure1);
end

% --- Executes on key press over figure1 with no controls selected.
function figure1_KeyPressFcn(hObject, evt)
% Check for "escape"
handles = guidata(hObject);
if isequal(get(hObject,'CurrentKey'),'escape')
    handles.output = '';    % User said no by hitting escape
    % Update handles structure
    guidata(hObject, handles);
    uiresume(handles.figure1);
end    


% --- Creates and returns a handle to the GUI figure. 
function nearneighbor_options_LayoutFcn(h1)

set(h1,...
'PaperUnits','centimeters',...
'CloseRequestFcn',@figure1_CloseRequestFcn,...
'Color',get(0,'factoryUicontrolBackgroundColor'),...
'KeyPressFcn',@figure1_KeyPressFcn,...
'MenuBar','none',...
'Name','nearneighbor_options',...
'NumberTitle','off',...
'Position',[265.768111202607 265.768111202607 238 192],...
'RendererMode','manual',...
'Resize','off',...
'Tag','figure1');

uicontrol('Parent',h1,...
'BackgroundColor',[1 1 1],...
'Call',{@main_uiCB,h1,'edit_EmptyNodes_CB'},...
'HorizontalAlignment','left',...
'Position',[10 167 47 21],...
'String','NaN',...
'Style','edit',...
'Tag','edit_EmptyNodes');

uicontrol('Parent',h1,...
'HorizontalAlignment','left',...
'Position',[61 169 65 16],...
'String','Empty nodes',...
'Style','text',...
'Tag','text_EmptyNodes');

uicontrol('Parent',h1,...
'BackgroundColor',[1 1 1],...
'Call',{@main_uiCB,h1,'popup_BoundaryCondition_CB'},...
'HorizontalAlignment','right',...
'Position',[10 143 47 21],...
'String',{  ''; 'x'; 'y'; 'xy'; 'g' },...
'Style','popupmenu',...
'Value',1,...
'Tag','popup_BoundaryCondition');

uicontrol('Parent',h1,...
'HorizontalAlignment','left',...
'Position',[61 145 95 16],...
'String','Boundary condition',...
'Style','text',...
'Tag','text_BoundaryCondition');

uicontrol('Parent',h1,...
'BackgroundColor',[1 1 1],...
'Call',{@main_uiCB,h1,'edit_Nsectrors_CB'},...
'HorizontalAlignment','left',...
'Position',[10 118 47 21],...
'String','4',...
'Style','edit',...
'Tag','edit_Nsectrors');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'checkbox_FourColumns_CB'},...
'Position',[11 91 95 21],...
'String','4 input columns',...
'Style','checkbox',...
'Tag','checkbox_FourColumns');

uicontrol('Parent',h1,...
'BackgroundColor',[1 1 1],...
'Call',{@main_uiCB,h1,'popup_FormatInput_CB'},...
'Enable','off',...
'Position',[10 64 91 22],...
'String','-f (inactive)',...
'Style','popupmenu',...
'Value',1,...
'Tag','popup_FormatInput');

uicontrol('Parent',h1,...
'FontSize',10,...
'FontWeight','bold',...
'HorizontalAlignment','left',...
'Position',[168 169 15 16],...
'String','-E',...
'Style','text');

uicontrol('Parent',h1,...
'FontSize',10,...
'FontWeight','bold',...
'HorizontalAlignment','left',...
'Position',[168 145 15 16],...
'String','-L',...
'Style','text');

uicontrol('Parent',h1,...
'FontSize',10,...
'FontWeight','bold',...
'HorizontalAlignment','left',...
'Position',[168 92 20 16],...
'String','-W',...
'Style','text');

uicontrol('Parent',h1,...
'FontSize',10,...
'FontWeight','bold',...
'HorizontalAlignment','left',...
'Position',[166 64 15 16.9],...
'String','-f',...
'Style','text');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'pushbutton_Cancel_CB'},...
'Position',[93 4 66 23],...
'String','Cancel',...
'Tag','pushbutton_Cancel');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'pushbutton_OK_CB'},...
'Position',[167 4 65 23],...
'String','OK',...
'Tag','pushbutton_OK');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'pushbutton_help_E_CB'},...
'Position',[200 168 30 18],...
'String','Help',...
'Tag','pushbutton_help_E');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'pushbutton_help_L_CB'},...
'Position',[200 144 30 18],...
'String','Help',...
'Tag','pushbutton_help_L');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'pushbutton_help_N_CB'},...
'Position',[200 119 30 18],...
'String','Help',...
'Tag','pushbutton_help_N');

uicontrol('Parent',h1,...
'Call',{@main_uiCB,h1,'pushbutton_help_W_CB'},...
'Position',[199 92 30 18],...
'String','Help',...
'Tag','pushbutton_help_W');

uicontrol('Parent',h1,...
'HorizontalAlignment','left',...
'Position',[61 121 55 16],...
'String','N� sectors',...
'Style','text');

uicontrol('Parent',h1,...
'FontSize',10,...
'FontWeight','bold',...
'HorizontalAlignment','left',...
'Position',[168 120 15 16],...
'String','-N',...
'Style','text');

uicontrol('Parent',h1,...
'BackgroundColor',[1 1 1],...
'Call',{@main_uiCB,h1,'edit_ShowCommand_CB'},...
'HorizontalAlignment','left',...
'Position',[10 33 221 21],...
'Style','edit',...
'Tag','edit_ShowCommand');

function main_uiCB(hObject, eventdata, h1, callback_name)
% This function is executed by the callback and than the handles is allways updated.
	feval(callback_name,hObject,guidata(h1));
